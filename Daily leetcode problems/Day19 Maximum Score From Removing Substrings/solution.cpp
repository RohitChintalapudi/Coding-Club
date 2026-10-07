#include <string>
#include <algorithm>

class Solution {
public:
    int maximumGain(std::string s, int x, int y) {
        int totalPoints = 0;
        std::string highPattern = x > y ? "ab" : "ba";
        std::string lowPattern = x > y ? "ba" : "ab";
        int highPoints = std::max(x, y);
        int lowPoints = std::min(x, y);

        std::string firstPass = "";
        for (char ch : s) {
            if (!firstPass.empty() && firstPass.back() == highPattern[0] && ch == highPattern[1]) {
                firstPass.pop_back();
                totalPoints += highPoints;
            } else {
                firstPass.push_back(ch);
            }
        }

        std::string secondPass = "";
        for (char ch : firstPass) {
            if (!secondPass.empty() && secondPass.back() == lowPattern[0] && ch == lowPattern[1]) {
                secondPass.pop_back();
                totalPoints += lowPoints;
            } else {
                secondPass.push_back(ch);
            }
        }

        return totalPoints;
    }
};
