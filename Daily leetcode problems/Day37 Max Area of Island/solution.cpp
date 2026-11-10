#include <vector>
#include <algorithm>

class Solution {
public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int best = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    best = std::max(best, dfs(grid, i, j, m, n));
                }
            }
        }
        return best;
    }

private:
    int dfs(std::vector<std::vector<int>>& grid, int r, int c, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != 1) {
            return 0;
        }
        grid[r][c] = 0;
        return 1 + dfs(grid, r + 1, c, m, n)
                 + dfs(grid, r - 1, c, m, n)
                 + dfs(grid, r, c + 1, m, n)
                 + dfs(grid, r, c - 1, m, n);
    }
};
