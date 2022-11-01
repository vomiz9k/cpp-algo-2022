// Coin change

#include <string>
#include <vector>
using namespace std;

/*
Идея: дп размера amount,
dp[i] = min(dp[i - coin] + 1 for coin in coins)
*/


class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        sort(coins.begin(), coins.end());
        dp[0] = 0;
        for(int i = 1; i <= amount; ++i) {
            for(int j = 0; j < coins.size(); ++j) {
                if (coins[j] > i) {
                    break;
                }
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
        if (dp[amount] > amount) {
            return -1;
        }
        return dp[amount];
    }
};
