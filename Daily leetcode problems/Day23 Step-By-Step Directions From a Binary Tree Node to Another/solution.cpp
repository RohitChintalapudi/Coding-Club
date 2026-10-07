#include <string>
#include <vector>
#include <algorithm>

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
    std::string getDirections(TreeNode* root, int startValue, int destValue) {
        std::string startPath = "";
        std::string destPath = "";

        findPath(root, startValue, startPath);
        findPath(root, destValue, destPath);

        int commonLen = 0;
        int minLen = std::min(startPath.size(), destPath.size());
        while (commonLen < minLen && startPath[commonLen] == destPath[commonLen]) {
            commonLen++;
        }

        std::string result = "";
        for (int i = commonLen; i < startPath.size(); ++i) {
            result += 'U';
        }

        result += destPath.substr(commonLen);

        return result;
    }

private:
    bool findPath(TreeNode* node, int target, std::string& path) {
        if (!node) {
            return false;
        }
        if (node->val == target) {
            return true;
        }

        path.push_back('L');
        if (findPath(node->left, target, path)) {
            return true;
        }
        path.pop_back();

        path.push_back('R');
        if (findPath(node->right, target, path)) {
            return true;
        }
        path.pop_back();

        return false;
    }
};
