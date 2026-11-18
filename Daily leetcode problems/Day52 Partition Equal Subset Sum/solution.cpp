#include <vector>
#include <numeric>

class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total % 2 != 0) return false;

        int target = total / 2;
        std::vector<bool> possible(target + 1, false);
        possible[0] = true;

        for (int num : nums) {
            for (int sum = target; sum >= num; --sum) {
                possible[sum] = possible[sum] || possible[sum - num];
            }
        }

        return possible[target];
    }
};
