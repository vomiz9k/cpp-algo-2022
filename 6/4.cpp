/*
Идея: алгоритм поиска мостов.
*/


class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        graph = std::vector<std::vector<int>>(n);
        for(const auto& connection: connections) {
            graph[connection[0]].push_back(connection[1]);
            graph[connection[1]].push_back(connection[0]);
        }
        used = std::vector<char>(n, false);
        enter = std::vector<int>(n, std::numeric_limits<int>::max());
        ret = std::vector<int>(n, std::numeric_limits<int>::max());
        result = std::vector<std::vector<int>>();
        dfs(0);
        return result;
    }

    std::vector<std::vector<int>> graph;
    std::vector<char> used;
    std::vector<int> enter;
    std::vector<int> ret;
    std::vector<std::vector<int>> result;

    void dfs(int v, int from=-1) {
        enter[v] = ret[v] = (from == -1 ? 0 : enter[from] + 1);
        used[v] = true;
        for(const int u: graph[v]) {
            if (u != from) {
                if (used[u]) {
                    ret[v] = std::min(ret[v], enter[u]);
                } else {
                    dfs(u, v);
                    ret[v] = std::min(ret[v], ret[u]);
                    if (ret[u] > enter[v]) {
                        result.push_back(std::vector<int>{u, v});
                    }
                }
            }
        }
    }
};