#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <algorithm>

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
        std::vector<std::vector<std::pair<int, int>>> graph(n + 1);
        for (const auto& edge : times) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }

        std::vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();

            if (time > dist[node]) continue;

            for (const auto& [next, weight] : graph[node]) {
                if (time + weight < dist[next]) {
                    dist[next] = time + weight;
                    pq.push({dist[next], next});
                }
            }
        }

        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1;
            answer = std::max(answer, dist[i]);
        }
        return answer;
    }
};
