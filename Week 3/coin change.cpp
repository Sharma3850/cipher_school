
// Coin Change -> Infinite Coins
// Subset Sum -> Finite Coins
// Rod Cutting
// 01 - Knapsack
// Edit Distance
// Longest Increasing Subsequence
// Longest Palindromic Substring/Subsequence
// Longest Increasing Path in the Matrix


// Coin Change -> Infinite Coins
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int N = coins.size();
        vector<vector<int>> dp(N + 1, vector<int>(amount + 1, INT_MAX));

        for (int i = 0; i <= N; i++) {
            dp[i][0] = 0;
        }

        for (int s = 1; s <= amount; s++) {
            for (int j = 1; j <= N; j++) {
                if (s >= coins[j - 1]) {
                    if (dp[j][s - coins[j - 1]] < INT_MAX) {
                        dp[j][s] = min(1 + dp[j][s - coins[j - 1]], dp[j - 1][s]);
                    }
                }
                else {
                    dp[j][s] = dp[j - 1][s];
                }
            }
        }

        return dp[N][amount] == INT_MAX ? -1 : dp[N][amount];
    }
};
