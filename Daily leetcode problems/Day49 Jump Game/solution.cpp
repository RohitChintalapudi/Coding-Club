#include <vector>
#include <algorithm>

class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int reach = 0;

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (i > reach) return false;
            reach = std::max(reach, i + nums[i]);
        }

        return true;
    }
};
