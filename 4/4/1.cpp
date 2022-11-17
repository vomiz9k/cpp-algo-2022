/*
Решение: идем по графу, при попадании на еще не посещенную вершину ищем бфсом
все вершины, лежащие с ней в компоненте связности


*/


class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        auto s = stack<std::pair<int, int>>();
        int result = 0;
        for(int i = 0; i < grid.size(); ++i) {
            for(int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == '1') {
                    s.push({i, j});
                    ++result;
                    while(!s.empty()) {
                        auto [x, y] = s.top();
                        s.pop();
                        if (x > 0 && grid[x - 1][y] == '1') {
                            s.push({x - 1, y});
                            grid[x - 1][y] = '0';
                        }
                        if (x < grid.size() - 1 && grid[x + 1][y] == '1') {
                            s.push({x + 1, y});
                            grid[x + 1][y] = '0';
                        }
                        if (y > 0 && grid[x][y - 1] == '1') {
                            s.push({x, y - 1});
                            grid[x][y - 1] = '0';
                        }
                        if (y < grid[0].size() - 1 && grid[x][y + 1] == '1') {
                            s.push({x, y + 1});
                            grid[x][y + 1] = '0';
                        }
                    }
                }
            }
        }
        return result;
    }
};