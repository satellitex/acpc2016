#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
typedef pair<int,int> P;
int ball[31];
int G[31][31];
int dp[30][30][5001];



int main(){
  int n,m,r;
  cin>>n>>m>>r;
  for(int i=0;i<n;i++) cin>>ball[i];

  for(int i=0;i<n;i++) 
    for(int j=0;j<n;j++)G[i][j]=INF;

  for(int i=0,a,b,c;i<m;i++){
    cin>>a>>b>>c;
    a--,b--;
    G[a][b]=G[b][a]=c;
  }
  
  for(int i=0;i<n;i++) G[i][i]=0;

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      for(int k=0;k<n;k++) G[i][j]=min(G[i][j],G[i][k]+G[k][j]);	

  memset(dp,-1,sizeof(dp));
  dp[0][0][0]=0;
  for(int t=0;t<=r;t++) //time
    for(int j=0;j<n;j++)//pos
    for(int i=0;i<n;i++) //pre
      for(int k=0;k<n;k++){//next
	  if(dp[i][j][t]==-1)continue;
	  int nball=dp[i][j][t]+ball[k];
	  if(i!=k&&j!=k)dp[j][k][t+G[j][k]]=max(dp[j][k][t+G[j][k]],nball);
	  else {
	    int cost=G[j][k]<8? 15-G[j][k]:G[j][k],a;
	    a=dp[j][k][t+cost]=max(dp[j][k][t+cost],nball);
	    int cost2=max(15,(cost+G[k][j]));
	    if(k!=j)dp[k][j][t+cost2]=max(dp[k][j][t+cost2],nball+ball[j]);
	  }
      }

  int ans=0;
  for(int i=0;i<n;i++)
    for(int j=0;j<=r;j++) ans=max(ans,dp[i][n-1][j]);
  cout <<ans<<endl;
  return 0;
}
