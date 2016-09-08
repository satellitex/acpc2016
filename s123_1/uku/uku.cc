#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 25;

int main()
{
  int N, M, R;
  cin >> N >> M >> R;

  int d[33];
  for(int i = 0; i < N; i++) cin >> d[i];

  int G[33][33], A[33][33];
  for(int i = 0; i < 33; i++) {
    for(int j = 0; j < 33; j++) G[i][j] = INF;
    G[i][i] = 0;
  }
  
  for(int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    G[a][b] = G[b][a] = c;
  }

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < N; k++) {
	G[j][k] = min(G[j][k], G[j][i] + G[i][k]);
      }
    }
  }

  for(int i = 0; i < N; i++) G[i][i] = 15;

  int dp[1010][33][33];
  memset(dp, -1, sizeof(dp));
  dp[0][0][0] = 0;
  for(int i = 0; i <= R; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < N; k++) {
	if(dp[i][j][k] == -1) continue;
	for(int l = 0; l < N; l++) {
	  int r = i + (j == l ? max(G[k][l], 15-G[k][l]) : G[k][l]);
	  int f = (j == l ? j : k);
	  if(r <= R)  dp[r][f][l] = max(dp[r][f][l], dp[i][j][k] + d[l]);
	}
      }
    }
  }
  
  int ans = 0;
  for(int i = 0; i <= R; i++) {
    for(int j = 0; j < N; j++) ans = max(ans, dp[i][j][N-1]);
  }

  cout << ans << endl;

  return 0;
}
