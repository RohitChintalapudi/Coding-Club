#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::string evaluateBracketPairs(std::string s,
                                    std::vector<std::vector<std::string>>& knowledge) {
        std::unordered_map<std::string, std::string> values;
        for (const auto& entry : knowledge) {
            values[entry[0]] = entry[1];
        }

        std::string result;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            if (s[i] != '(') {
                result += s[i];
                continue;
            }

            int j = i + 1;
            while (s[j] != ')') {
                ++j;
            }

            std::string key = s.substr(i + 1, j - i - 1);
            auto it = values.find(key);
            if (it != values.end()) {
                result += it->second;
            } else {
                result += '?';
            }

            i = j;
        }

        return result;
    }
};
