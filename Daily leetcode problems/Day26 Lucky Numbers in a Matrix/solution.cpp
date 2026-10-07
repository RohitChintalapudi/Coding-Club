#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> luckyNumbers(std::vector<std::vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        std::vector<int> rowMin(m, 1e9);
        std::vector<int> colMax(n, 0);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                rowMin[i] = std::min(rowMin[i], matrix[i][j]);
                colMax[j] = std::max(colMax[j], matrix[i][j]);
            }
        }

        std::vector<int> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == rowMin[i] && matrix[i][j] == colMax[j]) {
                    result.push_back(matrix[i][j]);
                }
            }
        }

        return result;
    }
};
