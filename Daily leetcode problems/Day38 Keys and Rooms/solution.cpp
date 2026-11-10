#include <vector>
#include <unordered_set>
#include <stack>

class Solution {
public:
    bool canVisitAllRooms(std::vector<std::vector<int>>& rooms) {
        std::unordered_set<int> visited;
        std::stack<int> st;
        st.push(0);

        while (!st.empty()) {
            int room = st.top();
            st.pop();
            if (visited.count(room)) continue;
            visited.insert(room);

            for (int key : rooms[room]) {
                if (!visited.count(key)) {
                    st.push(key);
                }
            }
        }

        return visited.size() == rooms.size();
    }
};
