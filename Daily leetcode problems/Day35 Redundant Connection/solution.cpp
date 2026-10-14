#include <vector>
#include <numeric>

class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector<std::vector<int>>& edges) {
        int n = edges.size();
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0);

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            if (!unionSets(u, v)) {
                return edge;
            }
        }

        return {};
    }

private:
    std::vector<int> parent;

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU == rootV) {
            return false;
        }
        parent[rootU] = rootV;
        return true;
    }
};
