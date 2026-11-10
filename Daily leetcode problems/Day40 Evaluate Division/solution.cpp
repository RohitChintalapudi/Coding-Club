#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class Solution {
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations,
                                    std::vector<double>& values,
                                    std::vector<std::vector<std::string>>& queries) {
        for (int i = 0; i < static_cast<int>(equations.size()); ++i) {
            graph[equations[i][0]].push_back({equations[i][1], values[i]});
            graph[equations[i][1]].push_back({equations[i][0], 1.0 / values[i]});
        }

        std::vector<double> results;
        results.reserve(queries.size());
        for (const auto& query : queries) {
            if (!graph.count(query[0]) || !graph.count(query[1])) {
                results.push_back(-1.0);
                continue;
            }
            std::unordered_set<std::string> visited;
            results.push_back(dfs(query[0], query[1], visited));
        }
        return results;
    }

private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> graph;

    double dfs(const std::string& current, const std::string& target,
               std::unordered_set<std::string>& visited) {
        if (current == target) return 1.0;
        visited.insert(current);

        for (const auto& edge : graph[current]) {
            if (visited.count(edge.first)) continue;
            double result = dfs(edge.first, target, visited);
            if (result != -1.0) {
                return edge.second * result;
            }
        }
        return -1.0;
    }
};
