#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int countPairs(TreeNode* root, int distance) {
        int count = 0;
        dfs(root, distance, count);
        return count;
    }

private:
    std::vector<int> dfs(TreeNode* node, int distance, int& count) {
        if (!node) {
            return {};
        }

        if (!node->left && !node->right) {
            return {1};
        }

        std::vector<int> leftDistances = dfs(node->left, distance, count);
        std::vector<int> rightDistances = dfs(node->right, distance, count);

        for (int l : leftDistances) {
            for (int r : rightDistances) {
                if (l + r <= distance) {
                    count++;
                }
            }
        }

        std::vector<int> currentDistances;
        for (int l : leftDistances) {
            if (l + 1 < distance) {
                currentDistances.push_back(l + 1);
            }
        }
        for (int r : rightDistances) {
            if (r + 1 < distance) {
                currentDistances.push_back(r + 1);
            }
        }

        return currentDistances;
    }
};
