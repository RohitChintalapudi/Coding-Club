#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<int> sortedNums = nums;
        std::sort(sortedNums.begin(), sortedNums.end());
        std::vector<std::vector<int>> result;

        int n = sortedNums.size();
        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && sortedNums[i] == sortedNums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = sortedNums[i] + sortedNums[left] + sortedNums[right];
                if (sum == 0) {
                    result.push_back({sortedNums[i], sortedNums[left], sortedNums[right]});
                    while (left < right && sortedNums[left] == sortedNums[left + 1]) ++left;
                    while (left < right && sortedNums[right] == sortedNums[right - 1]) --right;
                    ++left;
                    --right;
                } else if (sum < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        return result;
    }
};
