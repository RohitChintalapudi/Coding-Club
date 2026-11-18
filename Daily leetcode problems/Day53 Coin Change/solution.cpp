#include <vector>
#include <algorithm>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        std::vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for (int value = 1; value <= amount; ++value) {
            for (int coin : coins) {
                if (coin <= value) {
                    dp[value] = std::min(dp[value], dp[value - coin] + 1);
                }
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];
    }
};
