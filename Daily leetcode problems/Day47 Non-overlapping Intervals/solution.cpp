#include <vector>
#include <algorithm>

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return a[1] < b[1];
                  });

        int removals = 0;
        int lastEnd = intervals[0][1];

        for (int i = 1; i < static_cast<int>(intervals.size()); ++i) {
            if (intervals[i][0] < lastEnd) {
                ++removals;
            } else {
                lastEnd = intervals[i][1];
            }
        }

        return removals;
    }
};
