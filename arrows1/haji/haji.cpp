#include <bits/stdc++.h>
#define N 401
#define f first
#define s second
using namespace std;
typedef pair<int,int> P;
typedef pair<P,int> PP;
int dp[5][N][N],DP[6][N];

int main(){
  int n,m,L;
  vector<PP> a[5];
  cin>>n>>m>>L;
  for(int i=0,d,l,r,t;i<m;i++){
    cin>>d>>l>>r>>t;
    a[d].push_back(PP(P(r+l-1,l),t));
  }
  for(int i=0;i<5;i++) sort(a[i].begin(),a[i].end());
  
  for(int i=0;i<5;i++)
    for(int j=0;j<=L;j++)
      for(int k=0,idx=0,size=a[i].size();k<=n;k++){
	dp[i][j][k+1]=max(dp[i][j][k+1],dp[i][j][k]);
	while(idx<size&&a[i][idx].f.f<k)idx++;
	if(idx>=size)continue;
	int l=a[i][idx].f.s,r=a[i][idx].f.f,t=a[i][idx].s;
	if(k==r){
	  dp[i][j+1][r]=max(dp[i][j+1][r],dp[i][j][l-1]+t);
	  if(idx+1<size&&a[i][idx+1].f.f==k)idx++,k--;
	}
      }

  int ans=0;
  
  for(int i=0;i<5;i++)
    for(int j=0;j<=L;j++)
      for(int k=0;j+k<=L;k++)
	DP[i+1][j+k]=max(DP[i+1][j+k],DP[i][j]+dp[i][k][n]);

  
  for(int j=0;j<=L;j++)ans=max(ans,DP[5][j]);
  cout <<ans<<endl;

  return 0;
}
