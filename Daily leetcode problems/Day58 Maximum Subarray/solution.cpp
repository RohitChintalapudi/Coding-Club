#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int current = nums[0];
        int best = nums[0];

        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            current = std::max(nums[i], current + nums[i]);
            best = std::max(best, current);
        }

        return best;
    }
};
