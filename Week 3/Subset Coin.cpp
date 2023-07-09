// q1: Subset Sum -> Finite Coins

#include <bits/stdc++.h>
using namespace std;

bool isSubsetSum(int set[], int n, int sum)
{
	bool subset[n + 1][sum + 1];

	for (int i = 0; i <= n; i++)
		subset[i][0] = true;

	for (int i = 1; i <= sum; i++)
		subset[0][i] = false;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= sum; j++) {
			if (j < set[i - 1])
				subset[i][j] = subset[i - 1][j];
			if (j >= set[i - 1])
				subset[i][j]= subset[i - 1][j]	|| subset[i - 1][j - set[i - 1]];
		}
	}
	return subset[n][sum];
}
int main()
{
	int set[] = { 3, 34, 4, 12, 5, 2 };
	int sum = 9;
	int n = sizeof(set) / sizeof(set[0]);
	if (isSubsetSum(set, n, sum) == true)
		cout << "Found a subset with given sum";
	else
		cout << "No subset with given sum";
	return 0;
}

// q2: Rod Cutting

int rod_cutting_bottom_up(vector<int> prices,int n){
    int dp[n+1];

    dp[0] = 0;
    
    for (int i = 1; i <= n;i++){
        int ans = INT_MIN;
        for (int j = 0; j < i;j++){
            int cut = j + 1;
            int current_ans = prices[j] + dp[i - cut];
            ans = max(ans, current_ans);
        }
        dp[i] = ans;
    }
    return dp[n];
}

// q3: Longest Increasing Subsequence
int LongestIncreasingSum(vector<int> &num){
    int N=nums.size();
    int maxLen=1;
    vector<int> dp(N+1,1);
    for(int i=2;i<N;i++){
        for(int j=0;j<i;j++){
            dp[i]=max(dp[i], 1 + dp[j]);
            maxLen=max(maxLen , dp[i]);
        }
    }
    return maxLen;
}
// or 
class Solution { // 256 ms, faster than 42.84%
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (nums[i] > nums[j] && dp[i] < dp[j] + 1)
                    dp[i] = dp[j] + 1;
        return *max_element(dp.begin(), dp.end());
    }
};
