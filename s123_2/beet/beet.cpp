#include<bits/stdc++.h>
using namespace std;
int dp[20][10050][20]={};
int main(){
  int n,m,k,i,j,l,c;
  cin>>n>>m>>k;
  int a[n],b[n];
  for(i=0;i<n;i++) cin >> a[i];
  for(i=0;i<n;i++) cin >> b[i];
  for(i=0;i<n;i++){
    for(j=0;j<=m;j++){
      for(l=0;l<=b[i];l++){
	if(j+l>m) break;
	for(c=0;c<=k;c++){
	  dp[i+1][j+l][c+(l!=0)]=max(dp[i+1][j+l][c+(l!=0)],dp[i][j][c]+a[i]*l);
	}
      }
    }
  }
  int ans=0;
  for(i=0;i<=m;i++)
    for(j=0;j<=k;j++)
      ans=max(ans,dp[n][i][j]+m-i);
  cout << ans << endl;
  return 0;
}
