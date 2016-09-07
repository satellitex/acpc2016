#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> P;

vector< vector<int> > G;

int D[100001];

P dfs(int now, int prev, int step)
{
  P ret = P(step, now);
  D[now] = max(D[now], ret.first);
  for(int i = 0; i < G[now].size(); i++) {
    if(G[now][i] == prev) continue;
    P cost = dfs(G[now][i], now, step + 1);
    ret = max(ret, cost);
  }

  return ret;
}

int main()
{
  int N; cin >> N;
  G.resize(N + 1);
  for(int i = 0; i < N-1; i++) {
    int u, v; cin >> u >> v;
    u--, v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  P p = dfs(0, -1, 0);
  memset(D, 0, sizeof(D));
  P q = dfs(p.second, -1, 0);
  dfs(q.second, -1, 0);

  for(int i = 0; i < N; i++) {
    cout << (N-1)*2 - D[i] << endl;
  }
  
  return 0;
}
