#include <vector>
#include <queue>
#include <unordered_map>

class Solution {
public:
    std::vector<std::vector<int>> buildMatrix(int k, std::vector<std::vector<int>>& rowConditions, std::vector<std::vector<int>>& colConditions) {
        std::vector<int> rowOrder = topologicalSort(k, rowConditions);
        std::vector<int> colOrder = topologicalSort(k, colConditions);

        if (rowOrder.empty() || colOrder.empty()) {
            return {};
        }

        std::unordered_map<int, int> colPos;
        for (int j = 0; j < k; ++j) {
            colPos[colOrder[j]] = j;
        }

        std::vector<std::vector<int>> matrix(k, std::vector<int>(k, 0));
        for (int i = 0; i < k; ++i) {
            int val = rowOrder[i];
            int j = colPos[val];
            matrix[i][j] = val;
        }

        return matrix;
    }

private:
    std::vector<int> topologicalSort(int k, const std::vector<std::vector<int>>& conditions) {
        std::vector<std::vector<int>> adj(k + 1);
        std::vector<int> inDegree(k + 1, 0);

        for (const auto& cond : conditions) {
            adj[cond[0]].push_back(cond[1]);
            inDegree[cond[1]]++;
        }

        std::queue<int> q;
        for (int i = 1; i <= k; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> order;
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            order.push_back(curr);

            for (int neighbor : adj[curr]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        if (order.size() != k) {
            return {};
        }

        return order;
    }
};
