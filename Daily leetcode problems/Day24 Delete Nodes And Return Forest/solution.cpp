#include <vector>
#include <unordered_set>

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
    std::vector<TreeNode*> delNodes(TreeNode* root, std::vector<int>& to_delete) {
        std::unordered_set<int> deleteSet(to_delete.begin(), to_delete.end());
        std::vector<TreeNode*> forest;

        root = processNode(root, deleteSet, forest);
        if (root) {
            forest.push_back(root);
        }

        return forest;
    }

private:
    TreeNode* processNode(TreeNode* node, const std::unordered_set<int>& deleteSet, std::vector<TreeNode*>& forest) {
        if (!node) {
            return nullptr;
        }

        node->left = processNode(node->left, deleteSet, forest);
        node->right = processNode(node->right, deleteSet, forest);

        if (deleteSet.count(node->val)) {
            if (node->left) {
                forest.push_back(node->left);
            }
            if (node->right) {
                forest.push_back(node->right);
            }
            delete node;
            return nullptr;
        }

        return node;
    }
};
