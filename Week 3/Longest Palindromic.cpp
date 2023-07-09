// Longest Palindromic Substring/Subsequence
string longestPalindrome(string s){
    string result="";
    int len=s.size(), maxLen=0;
    vector<vector<int>> dp(len,vector<int>(len,0));
    for(int i=0;i<len;i++){
        dp[i][i]=1;
        if(maxLen < dp[i][i]){
            maxLen=dp[i][i];
            result=s.substr(i,1);
        }
    }
    int i,j;
    for(int window=w;window<=len;window++){
        for(int i=0;i<len-window+1;i++){
            j=i+window-1;
            if(window==2){
                if(s[i]==s[j]){
                    dp[i][j] = 2;
                    if(maxLen < dp[i][j]){
                        maxLen=dp[i][j];
                        result=s.substr(i,2);
                    }
                }
            }
            else{
                if(s[i]==s[j] && dp[i+1]>0){
                    dp[i][j] = window;
                    if(maxLen < dp[i][j]){
                        maxLen=dp[i][j];
                        result=s.substr(i,window);
                    }
                }
                else{
                    dp[i][j]=0;
                }
            }
        }
    }
}


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

// Longest Increasing Path in the Matrix
class Solution {
public:
    int ijToN(int i,int j,int m,int n){
        return n*i+(j);
    }
    pair<int,int> NToij(int N,int n,int m){
        int i=N/n;
        int j=N-i*n;
        return {i,j};
    }
    int dfs(pair<int,int>node,vector<int>adj[],vector<vector<int>>&vis,int num,int m,int n,vector<vector<int>>&store){
        vis[node.first][node.second]=1;
        if(adj[num].size()==0){
            store[node.first][node.second]=1;
            return 1;}
        int len=INT_MIN;
        for(auto it:adj[num]){
            auto neighbour=NToij(it,n,m);
            if(vis[neighbour.first][neighbour.second]==0){
                len=max(len,dfs(neighbour,adj,vis,it,m,n,store));
            }
            else{
                len=max(len,store[neighbour.first][neighbour.second]);
            }
        }
        store[node.first][node.second]=len+1;
        return len+1;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        queue<pair<pair<int,int>,int>>q;
        int m=matrix.size();
        int n=matrix[0].size();
        vector<int>adj[m*n];
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int num=ijToN(i,j,m,n);
                int dirRow[]={1,0,-1,0};
                int dirCol[]={0,1,0,-1};
                for(int k=0;k<4;k++){
                    int dx=i+dirRow[k];
                    int dy=j+dirCol[k];
                    if(dx>=0 and dx<m and dy>=0 and dy<n and matrix[dx][dy]>matrix[i][j]){
                        int numNew=ijToN(dx,dy,m,n);
                        adj[num].push_back(numNew);
                    }
                }
            }
        }
        vector<vector<int>>vis(m,vector<int>(n,0));
        vector<vector<int>>store(m,vector<int>(n,0));
        int ans=INT_MIN;
        for(int i=0;i<m*n;i++){
            auto node=NToij(i,n,m);
            if(vis[node.first][node.second]==0){
                int len=dfs(node,adj,vis,i,m,n,store);
                ans=max(ans,len);
            }
        }
        return ans;
    }
};
