#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <stack>

class Solution {
public:
    std::vector<int> survivedRobotsHealths(std::vector<int>& positions, std::vector<int>& healths, std::string directions) {
        int n = positions.size();
        std::vector<int> indices(n);
        std::iota(indices.begin(), indices.end(), 0);

        std::sort(indices.begin(), indices.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        std::stack<int> st;

        for (int curr : indices) {
            if (directions[curr] == 'R') {
                st.push(curr);
            } else {
                while (!st.empty() && healths[curr] > 0) {
                    int top = st.top();
                    if (healths[top] < healths[curr]) {
                        healths[top] = 0;
                        healths[curr] -= 1;
                        st.pop();
                    } else if (healths[top] > healths[curr]) {
                        healths[top] -= 1;
                        healths[curr] = 0;
                    } else {
                        healths[top] = 0;
                        healths[curr] = 0;
                        st.pop();
                    }
                }
            }
        }

        std::vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (healths[i] > 0) {
                result.push_back(healths[i]);
            }
        }

        return result;
    }
};
