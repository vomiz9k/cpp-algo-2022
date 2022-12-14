


/*

Просто алгоритм Прима.

*/




class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        vector<bool> visited(points.size(), false);
        int result = 0;
        int processed = 0;
        heap.emplace(0, 0);
        while(processed < points.size()) {
            auto [cost, u] = heap.top();
            heap.pop();
            if (visited[u]) {
                continue;
            }
            visited[u] = true;
            result += cost;
            ++processed;

            for(int i = 0; i < points.size(); ++i) {
                if (!visited[i]) {
                    heap.emplace(abs(points[i][0] - points[u][0]) + abs(points[i][1] - points[u][1]), i);
                }
            }
        }
        return result;
    }
};