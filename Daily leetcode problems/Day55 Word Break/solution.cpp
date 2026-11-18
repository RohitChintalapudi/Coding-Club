#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        int n = static_cast<int>(s.size());

        std::vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
