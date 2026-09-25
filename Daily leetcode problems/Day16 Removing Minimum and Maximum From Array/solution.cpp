#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumDeletions(std::vector<int>& nums) {
        int n = nums.size();
        int mi = 0, mx = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < nums[mi]) {
                mi = i;
            }
            if (nums[i] > nums[mx]) {
                mx = i;
            }
        }
        if (mi > mx) {
            std::swap(mi, mx);
        }
        return std::min({mx + 1, n - mi, (mi + 1) + (n - mx)});
    }
};
