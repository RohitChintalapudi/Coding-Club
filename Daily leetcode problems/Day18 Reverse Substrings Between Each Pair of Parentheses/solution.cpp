#include <string>
#include <stack>
#include <algorithm>

class Solution {
public:
    std::string reverseParentheses(std::string s) {
        std::string result;
        std::stack<int> open;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                open.push(result.size());
            } else if (s[i] == ')') {
                int start = open.top();
                open.pop();
                std::reverse(result.begin() + start, result.end());
            } else {
                result += s[i];
            }
        }

        return result;
    }
};
