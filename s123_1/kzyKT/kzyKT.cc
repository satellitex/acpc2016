#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
typedef pair<int,P> PP;
int dp[1111][31][31][9][2][2],a[31];

int main() {
  int n,m,t;
  cin >> n >> m >> t;
  vector<PP> v[n];
  for(int i=0; i<n; i++) cin >> a[i];
  for(int i=0; i<m; i++) {
    int x,y,z;
    cin >> x >> y >> z;
    x--,y--;
    v[x].push_back(PP(y,P(z,a[y])));
    v[y].push_back(PP(x,P(z,a[x])));
    v[x].push_back(PP(x,P(15,a[x])));
    v[y].push_back(PP(y,P(15,a[y])));
  }
  memset(dp,-1,sizeof(dp));
  dp[0][0][0][8][0][0]=0;
  for(int i=0; i<t; i++)
    for(int x=0; x<n; x++)
      for(int j=0; j<n; j++)
        for(int k=5; k<9; k++)
          for(int f=0; f<2; f++)
            for(int h=0; h<2; h++) {
              if(dp[i][x][j][k][f][h]==-1) continue;
              for(int l=0; l<v[x].size(); l++) {
                PP p=v[x][l];
                int y=p.first,c=p.second.first,d=p.second.second;
                if(!h||y!=j) dp[i+c][y][x][min(8,c)][1][f]=max(dp[i+c][y][x][min(8,c)][1][f],dp[i][x][j][k][f][h]+d);
                else {
                  dp[i+c][y][x][min(8,c)][0][f]=max(dp[i+c][y][x][min(8,c)][0][f],dp[i][x][j][k][f][h]);
                  int z=max(0,15-(k<8?k:15)-c);
                  dp[i+c+z][y][x][min(8,c+z)][1][f]=max(dp[i+c+z][y][x][min(8,c+z)][1][f],dp[i][x][j][k][f][h]+d);
                }
              }
            }
  int ans=0;
  for(int i=0; i<=t; i++)
    for(int j=0; j<n; j++)
      for(int k=0; k<9; k++)
        for(int l=0; l<2; l++)
          for(int f=0; f<2; f++) ans=max(ans,dp[i][n-1][j][k][l][f]);
  cout << ans << endl;
  return 0;
}
