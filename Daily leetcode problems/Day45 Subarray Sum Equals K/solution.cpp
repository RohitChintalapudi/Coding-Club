#include <vector>
#include <unordered_map>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> prefixCount;
        prefixCount[0] = 1;

        int count = 0;
        int prefixSum = 0;

        for (int num : nums) {
            prefixSum += num;

            auto it = prefixCount.find(prefixSum - k);
            if (it != prefixCount.end()) {
                count += it->second;
            }

            ++prefixCount[prefixSum];
        }

        return count;
    }
};
