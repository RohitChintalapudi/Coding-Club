#include <vector>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int islands = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    ++islands;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return islands;
    }

private:
    void dfs(std::vector<std::vector<char>>& grid, int r, int c, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] != '1') {
            return;
        }
        grid[r][c] = '0';
        dfs(grid, r + 1, c, m, n);
        dfs(grid, r - 1, c, m, n);
        dfs(grid, r, c + 1, m, n);
        dfs(grid, r, c - 1, m, n);
    }
};
