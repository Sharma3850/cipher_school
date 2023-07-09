// 01 - Knapsack
class Solution {
public:
    int findTargetSumWays(vector<int>& arr, int target) {
        int n=arr.size();
        int sum=0;
        for(auto it:arr) sum+=it;
        if(sum-target<0 || (sum+target)%2 || target+sum<0) return 0;
        if(target<-1*sum) return 0;
        int val=(sum+target)/2;
        vector<vector<int>> dp(n,vector<int>(val+1,0));
        if(arr[0] == 0) dp[0][0] =2;  
        else dp[0][0] = 1;  
        if(arr[0]!=0 && arr[0]<=val) dp[0][arr[0]] = 1; 
        for(int i=1;i<n;i++){
            for(int s=0;s<=val;s++){
                int take = 0;
                if(arr[i]<=s) take=dp[i-1][s-arr[i]];
                int notTake= dp[i-1][s];
                dp[i][s]=take+notTake;
            }
        }
        return dp[n-1][val];
    }
};
// C++ program for the above approach

#include <bits/stdc++.h>
using namespace std;

int knapSack(int W, int wt[], int val[], int n)
{
	int dp[W + 1];
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i < n + 1; i++) {
		for (int w = W; w >= 0; w--) {

			if (wt[i - 1] <= w)
				dp[w] = max(dp[w],
							dp[w - wt[i - 1]] + val[i - 1]);
		}
	}
	return dp[W];
}

int main()
{
	int profit[] = { 60, 100, 120 };
	int weight[] = { 10, 20, 30 };
	int W = 50;
	int n = sizeof(profit) / sizeof(profit[0]);
	cout << knapSack(W, weight, profit, n);
	return 0;
}

// 516. Longest Palindromic Subsequence
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int len = s.size();
        int maxLen = 0;
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for (int i = 0; i < len; i++) {
            dp[i][i] = 1;
            if (maxLen < dp[i][i]) {
                maxLen = dp[i][i];
            }
        }
        int i, j;
        for (int window = 2; window <= len; window++) {
            for (i = 0; i < len - window + 1; i++) {
                j = i + window - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                    if (maxLen < dp[i][j]) {
                        maxLen = dp[i][j];
                    }
                }
                else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
        return maxLen;
    }
};
