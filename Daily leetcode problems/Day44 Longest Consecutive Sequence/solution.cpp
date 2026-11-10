#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        int longest = 0;

        for (int num : numSet) {
            if (numSet.count(num - 1)) continue;

            int length = 1;
            while (numSet.count(num + length)) {
                ++length;
            }
            longest = std::max(longest, length);
        }

        return longest;
    }
};
