#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
int dp[1600][301],ans;
int main(){
  int n,m,l;
  vector<P> v[1600];
  cin>>n>>m>>l;
  for(int i=0,d,a,k,t;i<m;i++)
    cin>>d>>a>>k>>t,v[d*n+a].push_back(P(k,t));
  for(int i=1;i<=5*n;i++)
    for(int k=0;k<=l;k++){
      for(int o=0;o<v[i].size();o++)
	  dp[i+v[i][o].first][k+1]=
	    max(dp[i][k]+v[i][o].second,dp[i+v[i][o].first][k+1]);
	dp[i+1][k]=max(dp[i][k],dp[i+1][k]);
      }
  for(int i=0;i<=l;i++)ans=max(ans,dp[5*n+1][i]);
  cout<<ans<<endl;
  return 0;
}
