#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

class Solution {
public:
    int minCostConnectPoints(std::vector<std::vector<int>>& points) {
        int n = points.size();
        if (n < 2) return 0;

        std::vector<int> minDist(n, INT_MAX);
        std::vector<bool> inMST(n, false);
        int totalCost = 0;

        minDist[0] = 0;
        for (int step = 0; step < n; ++step) {
            int u = -1;
            for (int v = 0; v < n; ++v) {
                if (!inMST[v] && (u == -1 || minDist[v] < minDist[u])) {
                    u = v;
                }
            }

            inMST[u] = true;
            totalCost += minDist[u];

            for (int v = 0; v < n; ++v) {
                if (!inMST[v]) {
                    int cost = std::abs(points[u][0] - points[v][0])
                             + std::abs(points[u][1] - points[v][1]);
                    minDist[v] = std::min(minDist[v], cost);
                }
            }
        }

        return totalCost;
    }
};
