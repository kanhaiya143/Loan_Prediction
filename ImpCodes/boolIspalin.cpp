/You are required to complete this function/
bool is_k_palin(string s,int k)
{
    
    string r=s;
    reverse(r.begin(),r.end());
    int n=r.size();
    int dp[n+1][n+1];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i==0||j==0)
            dp[i][j]=0;
            else if(s[i-1]==r[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    int len=dp[n][n];
    if(n-len<=k)
    return true;
    return false;
    
    
//Your code here
}
