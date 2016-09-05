#include<bits/stdc++.h>
#define INF (1e9)
#define R 4005
#define N 30
using namespace std;
typedef pair<int,int> P;
int n,m,r,a,b,c,d[N],t[N][N],ans;
int dp[R][N][N];

int main(){
  cin>>n>>m>>r;
  for(int i=0;i<n;i++)cin>>d[i];

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)t[i][j]=INF;
  for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    t[a-1][b-1]=c;
    t[b-1][a-1]=c;
  }

  for(int k=0;k<n;k++)
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
	t[i][j]=min(t[i][j],t[i][k]+t[k][j]);
  for(int i=0;i<n;i++)t[i][i]=15;
  memset(dp,-1,sizeof(dp));
  dp[0][0][0]=0;
  for(int i=0;i<=r;i++)
    for(int j=0;j<n;j++)
      for(int k=0;k<n;k++){
	if(dp[i][j][k]<0)continue;
	for(int l=0;l<n;l++){
	  if(k==l){
	    int x=max(0,15-t[j][l]*2);
	    dp[i+t[j][l]+x][l][j]=
	      max(dp[i+t[j][l]+x][l][j],dp[i][j][k]+d[l]);
	    dp[i+t[j][l]*2+x][j][l]=
	      max(dp[i+t[j][l]*2+x][j][l],dp[i][j][k]+d[j]+d[l]);
	  }else
	    dp[i+t[j][l]][l][j]=
	      max(dp[i+t[j][l]][l][j],dp[i][j][k]+d[l]);
	}
      }
  for(int i=0;i<=r;i++)
    for(int j=0;j<n;j++)ans=max(ans,dp[i][n-1][j]);
  cout<<ans<<endl;
  return 0;
}
