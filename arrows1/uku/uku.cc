#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, M, L;
  cin >> N >> M >> L;

  int k[303], t[303];
  vector<int> sche[45];
  for(int i = 0; i < M; i++) {
    int d, a;
    cin >> d >> a >> k[i] >> t[i];
    a += N*d;
    sche[a].push_back(i);
  }
  
  int dp[45][45] = {{0}};
  for(int i = 0; i <= N*5; i++) {
    for(int j = 0; j <= L; j++) {
      dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
      if(j == L) continue;
      for(int l = 0; l < sche[i].size(); l++) {
	int idx = sche[i][l];
	dp[i+k[idx]][j+1] = max(dp[i+k[idx]][j+1], dp[i][j] + t[idx]);
      }
    }
  }

  cout << *max_element(dp[0], dp[N*5 + 2]) << endl;
  
  return 0;
}
