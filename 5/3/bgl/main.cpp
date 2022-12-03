#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/subgraph.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/properties.hpp>

#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/spirit/include/qi.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <charconv>
#include <deque>

/*

Я убил на эту вещь непозволительно большое количество времени, на наведение красоты в коде времени тратить не стал, прошу не судить строго.
Если вы на семинаре разберете крутое и лаконичное решение этой задачи -- буду очень рад, потому что опыт знакомства с BGL мне пока не очень зашел.

*/

typedef std::pair<int, int> EdgeIdWeight;
typedef boost::property<boost::edge_index_t, int, boost::property<boost::edge_weight_t, int, boost::property<boost::edge_color_t, std::string>>> EdgeProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeProperty> Graph;
typedef std::pair<int, int> Edge;

template<typename Weightmap, typename Idmap>
class dfs_mst_pseudo_critical_visitor : public boost::default_dfs_visitor {
public:
    dfs_mst_pseudo_critical_visitor(std::vector<int>& edges, int weight, Weightmap& weightmap, Idmap& idmap)
    : edges(edges), weight(weight), weightmap(weightmap), idmap(idmap) {}

    template<typename E, typename G>
    void examine_edge(E edge, const G & graph) const {
        if (weightmap[edge] == weight) {
            edges.push_back(idmap[edge]);
        }
    }

    std::vector<int>& edges;
    int weight;
    Weightmap& weightmap;
    Idmap& idmap;
};

template<typename Idmap>
class bfs_mst_critical_visitor : public boost::default_bfs_visitor {
public:
    bfs_mst_critical_visitor(const std::set<int>& pseudo_critical, std::vector<int>& critical, Idmap& idmap)
    :  pseudo_critical(pseudo_critical), critical(critical), idmap(idmap) {}

    template<typename E, typename G>
    void examine_edge(E edge, const G & graph) const {
        if (pseudo_critical.count(idmap[edge]) == 0) {
            critical.push_back(idmap[edge]);
        }
    }

    const std::set<int>& pseudo_critical;
    std::vector<int>& critical;
    Idmap& idmap;
};


Graph parseInputGraph(const std::string& filename) {
    std::ifstream in(filename);
    int length;
    in.seekg(0, std::ios::end);
    length = in.tellg();
    in.seekg(0, std::ios::beg);
    char* buffer = new char[length + 1];
    in.read(buffer, length + 1);
    in.close();

    std::string_view input_view(buffer);

    std::deque<int> data;

    boost::spirit::qi::parse(input_view.begin(), input_view.end(),
        "n = " >> boost::spirit::qi::int_ >> ", edges = " >> '[' >> ('[' >> boost::spirit::qi::int_ % ',' >> ']') % ',' >> ']',
        data);

    int n = data.front();
    data.pop_front();

    std::vector<Edge> edges;
    std::vector<EdgeProperty> props;
    if (data.size() % 3 != 0) {
        throw;
    }

    for(size_t i = 0; i < data.size(); i += 3) {
        edges.emplace_back(data[i], data[i + 1]);
        props.emplace_back(i / 3, data[i + 2]);
    }

    Graph result(n);
    for(size_t i = 0; i < edges.size(); ++i) {
        boost::add_edge(edges[i].first, edges[i].second, props[i], result);
    }

    return result;
}

std::pair<std::vector<int>, std::vector<int>> findCriticalAndPreudoCriticalEdges(const boost::program_options::variables_map& vm) {
    Graph graph =  parseInputGraph(vm["inputGraph"].as<std::string>());

    auto weightmap = get(boost::edge_weight, graph);
    auto idmap    =  get(boost::edge_index, graph);


    std::ofstream out(vm["outputGraph.dot"].as<std::string>());
    boost::dynamic_properties dp;
    dp.property("node_id", get(boost::vertex_index, graph));
    dp.property("label", weightmap);
    dp.property("index", idmap);

    boost::write_graphviz_dp(out, graph ,dp);

    std::vector<unsigned int>spanning_tree;
    std::vector < boost::graph_traits < Graph >::vertex_descriptor >  p(boost::num_vertices(graph));
    boost::prim_minimum_spanning_tree(graph, &p[0]);


    Graph mst;
    auto weightmap_mst = get(boost::edge_weight, mst);

    for(size_t i = 0; i < p.size(); ++i) {
        if (i != p[i]) {
            auto e = boost::edge(i, p[i], graph).first;
            boost::add_edge(i, p[i], *(EdgeProperty*)e.get_property(), mst);
        }
    }

    std::ofstream out2(vm["outputMST.dot"].as<std::string>());
    boost::dynamic_properties dp2;

    dp2.property("node_id", get(boost::vertex_index, mst));
    dp2.property("label", weightmap_mst);

    boost::write_graphviz_dp(out2, mst, dp2);

    std::vector<int> pseudo_critical;
    std::vector<int> critical;

    auto es = boost::edges(graph);
    for (auto eit = es.first; eit != es.second; ++eit) {
        auto from = boost::source(*eit, graph);
        auto to = boost::target(*eit, graph);
        if (!boost::edge(from, to, mst).second) {
            auto prev_cnt = pseudo_critical.size();
            dfs_mst_pseudo_critical_visitor v(pseudo_critical, weightmap[*eit], weightmap, idmap);
            boost::depth_first_search(mst, boost::visitor(v));
            if (pseudo_critical.size() > prev_cnt) {
                pseudo_critical.emplace_back(idmap[*eit]);
            }
        }
    }

    std::set<int> pseudo_critical_set(pseudo_critical.begin(), pseudo_critical.end());

    bfs_mst_critical_visitor v(pseudo_critical_set, critical, idmap);
    boost::breadth_first_search(mst, 0, boost::visitor(v));
    std::set<int> critical_set(critical.begin(), critical.end());



    auto colormap = get(boost::edge_color, graph);
    es = boost::edges(graph);
    for (auto eit = es.first; eit != es.second; ++eit) {
        if (pseudo_critical_set.count(idmap[*eit])) {
            colormap[*eit] = "dodgerblue4";
        } else if (critical_set.count(idmap[*eit])) {
            colormap[*eit] = "firebrick1";
        } else {
            colormap[*eit] = "gray0";
        }
    }

    dp.property("color", colormap);
    std::ofstream out3(vm["outputCriticalAndPseusocriticalEdges.dot"].as<std::string>());

    boost::write_graphviz_dp(out3, graph ,dp);

    return {{critical_set.begin(), critical_set.end()}, {pseudo_critical_set.begin(), pseudo_critical_set.end()}};
}

int main(int argc, char* argv[]) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("inputGraph", boost::program_options::value<std::string>()->default_value("inputGraph"), "input graph file path")
        ("outputGraph.dot", boost::program_options::value<std::string>()->default_value("outputGraph.dot"), "output graph file path")
        ("outputMST.dot", boost::program_options::value<std::string>()->default_value("outputMST.dot"), "output MST file path")
        ("outputCriticalAndPseusocriticalEdges.dot", boost::program_options::value<std::string>()->default_value("outputCriticalAndPseusocriticalEdges.dot"), "output MST file path")
    ;

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }
    auto [critical, pseudo_critical] = findCriticalAndPreudoCriticalEdges(vm);

    for(const auto edge: critical) {
        std::cout << edge << ' ';
    } std::cout << '\n';

    for(const auto edge: pseudo_critical) {
        std::cout << edge << ' ';
    } std::cout << '\n';
}