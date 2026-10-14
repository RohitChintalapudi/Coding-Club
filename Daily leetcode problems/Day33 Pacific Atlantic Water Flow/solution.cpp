#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};
        int m = heights.size();
        int n = heights[0].size();

        std::vector<std::vector<bool>> pacific(m, std::vector<bool>(n, false));
        std::vector<std::vector<bool>> atlantic(m, std::vector<bool>(n, false));

        for (int i = 0; i < m; ++i) {
            dfs(heights, pacific, i, 0, m, n);
            dfs(heights, atlantic, i, n - 1, m, n);
        }

        for (int j = 0; j < n; ++j) {
            dfs(heights, pacific, 0, j, m, n);
            dfs(heights, atlantic, m - 1, j, m, n);
        }

        std::vector<std::vector<int>> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }

private:
    void dfs(const std::vector<std::vector<int>>& heights, std::vector<std::vector<bool>>& visited, int r, int c, int m, int n) {
        visited[r][c] = true;
        const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (int k = 0; k < 4; ++k) {
            int nr = r + dirs[k][0];
            int nc = c + dirs[k][1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                dfs(heights, visited, nr, nc, m, n);
            }
        }
    }
};
