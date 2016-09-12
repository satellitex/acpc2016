#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef pair<int,int> P;
typedef pair<int,P> PP;

int dp[5][1<<8][301],dp2[6][301];
int main() {
  int n,m,l;
  cin >> n >> m >> l;
  vector<PP> a[5];
  for(int i=0,x,y,z,w; i<m; i++) {
    cin >> x >> y >> z >> w;
    a[x].push_back(PP(y-1,P(z,w)));
  }
  for(int s=0; s<5; s++) {
    for(int t=0; t<(1<<n); t++) {
      for(int k=0; k<a[s].size(); k++) {
        for(int i=0; i<a[s].size(); i++) {
          int c=0;
          for(int j=a[s][i].F; j<a[s][i].F+a[s][i].S.F; j++) c|=t&(1<<j);
          if(c) continue;
          int tt=t;
          for(int j=a[s][i].F; j<a[s][i].F+a[s][i].S.F; j++) tt|=1<<j;
          dp[s][tt][k+1]=max(dp[s][tt][k+1],dp[s][t][k]+a[s][i].S.S);
        }
      }
    }
  }
  for(int i=0; i<5; i++) {
    for(int k=0; k<=m; k++) {
      for(int t=0; t<(1<<n); t++) {
        for(int j=0; j<=a[i].size(); j++) {
          if(k+j<301) dp2[i+1][k+j]=max(dp2[i+1][k+j],dp2[i][k]+dp[i][t][j]);
        }
      }
    }
  }
  int ans=0;
  for(int i=0; i<=l; i++) ans=max(ans,dp2[5][i]);
  cout << ans << endl;
  return 0;
}
