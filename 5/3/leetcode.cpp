
/*

Идея: строим мст. (a, b) - ребро не из мст, тогда, если в мст на пути из а до б есть ребра, равные по стоимости (a, b) -- то (a, b) и все эти ребра -- псевдо-критические.
Критические -- все ребра из мст, не являющиеся псевдо-критическими.

*/


class Solution {
public:
    set<int> dfs(int from, int to, int weight, vector<vector<int>>& mst, vector<vector<int>>& edges) {
        set<int> result;
        dfs(from, to, weight, mst, edges, result, -1);
        return result;
    }

    bool dfs(int from, int to, int weight, vector<vector<int>>& mst, vector<vector<int>>& edges, set<int>& result, int prev_edge) {
        if (to == from) {
            return true;
        }
        for(const auto edge: mst[from]) {
            if (edge != prev_edge) {
                int new_from = edges[edge][0] == from ? edges[edge][1] : edges[edge][0];
                if (dfs(new_from, to, weight, mst, edges, result, edge)) {
                    if (weight == edges[edge][2]) {
                        result.insert(edge);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>(n));
        for(int i = 0; i < edges.size(); ++i) {
            edges[i].push_back(i);
            graph[edges[i][0]][edges[i][1]] = {edges[i][2], i};
            graph[edges[i][1]][edges[i][0]] = {edges[i][2], i};
        }

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> heap;
        vector<bool> visited(n, false);
        vector<vector<int>> mst(n);
        set<int> mst_edges;
        int processed = 0;
        heap.emplace(0, 0, -1);
        while(processed < n) {
            auto [cost, u, num] = heap.top();
            heap.pop();
            if (visited[u]) {
                continue;
            }
            visited[u] = true;
            ++processed;
            if (num != -1) {
                mst[edges[num][0]].push_back(num);
                mst[edges[num][1]].push_back(num);
                mst_edges.insert(num);
            }

            for(int i = 0; i < n; ++i) {
                if (!visited[i] && graph[u][i].first != 0) {
                    heap.emplace(graph[u][i].first, i, graph[u][i].second);
                }
            }
        }

        set<int> pseudo_critical;
        for(const auto& edge: edges) {
            if (mst_edges.count(edge[3]) == 0) {
                auto s = dfs(edge[0], edge[1], edge[2], mst, edges);
                if (!s.empty()) {
                    pseudo_critical.insert(s.begin(), s.end());
                    pseudo_critical.insert(edge[3]);
                }
            }
        }

        vector<int> critical;
        for (auto edge: mst_edges) {
            if (pseudo_critical.count(edge) == 0) {
                critical.push_back(edge);
            }
        }

        return {critical, vector<int>(pseudo_critical.begin(), pseudo_critical.end())};
    }
};