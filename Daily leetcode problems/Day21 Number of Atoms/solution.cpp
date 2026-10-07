#include <string>
#include <map>
#include <stack>
#include <cctype>

class Solution {
public:
    std::string countOfAtoms(std::string formula) {
        int n = formula.length();
        int i = 0;
        std::stack<std::map<std::string, int>> st;
        st.push({});

        while (i < n) {
            if (formula[i] == '(') {
                st.push({});
                i++;
            } else if (formula[i] == ')') {
                std::map<std::string, int> top = st.top();
                st.pop();
                i++;
                int start = i;
                while (i < n && isdigit(formula[i])) {
                    i++;
                }
                int multiplier = start < i ? std::stoi(formula.substr(start, i - start)) : 1;
                for (auto& [atom, count] : top) {
                    st.top()[atom] += count * multiplier;
                }
            } else {
                int start = i++;
                while (i < n && islower(formula[i])) {
                    i++;
                }
                std::string atom = formula.substr(start, i - start);
                int countStart = i;
                while (i < n && isdigit(formula[i])) {
                    i++;
                }
                int count = countStart < i ? std::stoi(formula.substr(countStart, i - countStart)) : 1;
                st.top()[atom] += count;
            }
        }

        std::string result = "";
        for (auto& [atom, count] : st.top()) {
            result += atom;
            if (count > 1) {
                result += std::to_string(count);
            }
        }

        return result;
    }
};
