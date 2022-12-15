
/*

Идея: чтобы найти искомый путь, нужно найти такую вершину x, что
min_cost(src1, x) + min_cost(src2, x) + min_cost(x, dest) минимально.

*/

class Solution {
public:
    static vector<long long> dijkstra(const vector<vector<pair<int, int>>>& graph, int from) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        vector<long long> dist(graph.size(), -1);
        dist[from] = 0;
        heap.emplace(0, from);
        while (!heap.empty()) {
            auto [cost, u] = heap.top();
            heap.pop();
            if (cost <= dist[u]) {
                for (auto [v, c] : graph[u]) {
                    if (dist[v] > dist[u] + c || dist[v] == -1) {
                        dist[v] = dist[u] + c;
                        heap.emplace(dist[v], v);
                    }
                }
            }
        }
        return dist;
    }

    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pair<int, int>>> graph(n), reversed_graph(n);
        for (const auto& edge: edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            reversed_graph[edge[1]].emplace_back(edge[0], edge[2]);
        }
        const auto dists_src1 = dijkstra(graph, src1);
        const auto dists_src2 = dijkstra(graph, src2);
        const auto dists_dest = dijkstra(reversed_graph, dest);

        long long result = -1;
        for(int i = 0; i < n; ++i) {
            if (dists_src1[i] != -1 && dists_src2[i] != -1 && dists_dest[i] != -1) {
                if (dists_src1[i] + dists_src2[i] + dists_dest[i] < result || result == -1) {
                    result = dists_src1[i] + dists_src2[i] + dists_dest[i];
                }
            }
        }
        return result;
    }
};