#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define REP(i,a,b) for(int i=a;i<(int)b;i++)
#define rep(i,n) REP(i,0,n)
#define all(c) (c).begin(), (c).end()
#define zero(a) memset(a, 0, sizeof a)
#define minus(a) memset(a, -1, sizeof a)
#define watch(a) { cout << #a << " = " << a << endl; }
template<class T1, class T2> inline bool minimize(T1 &a, T2 b) { return b < a && (a = b, 1); }
template<class T1, class T2> inline bool maximize(T1 &a, T2 b) { return a < b && (a = b, 1); }

typedef long long ll;

int const NMin = 2;
int const NMax = 100000;

int N;
int u[NMax], v[NMax];

vector<vector<int>> G;

int main() {

  registerValidation();

  N = inf.readInt(NMin, NMax);
  inf.readEoln();
  rep(i, N - 1) {
    u[i] = inf.readInt(1, NMax);
    inf.readSpace();
    v[i] = inf.readInt(1, NMax);
    ensuref(u[i] != v[i], "error: u = v");
    inf.readEoln();
  }
  inf.readEof();

  G.resize(N);
  rep(i, N - 1) {
    G[u[i] - 1].push_back(v[i] - 1);
    G[v[i] - 1].push_back(u[i] - 1);
  }

  queue<int> q;
  q.push(0);

  vector<bool> vis(N);
  vis[0] = 1;

  while(!q.empty()) {
    int curr = q.front(); q.pop();
    for(int next: G[curr]) {
      if(vis[next]) continue;
      vis[next] = 1;
      q.push(next);
    }
  }

  rep(i, N) {
    ensuref(vis[i], "error: unconnected");
  }

  return 0;
}