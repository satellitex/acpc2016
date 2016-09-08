#include <bits/stdc++.h>

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
int const inf = 1<<29;
typedef pair<int, int> pii;

int main() {

  int N, M; cin >> N >> M;
  vector<vector<pii> > g(N);

  rep(i, M) {
    int a, b, c; cin >> a >> b >> c;
    a--, b--;
    g[a].push_back(make_pair(b, c));
  }
  
  priority_queue<pii, vector<pii>, greater<pii> > pq;
  pq.push(make_pair(0, 0));

  vector<int> dist(N, inf);
  dist[0] = 0;

  int ans = -1;

  while(!pq.empty()) {
    pii p = pq.top(); pq.pop();
    int weight = p.first, curr = p.second;

    for(int i=0; i<g[curr].size(); i++) {
      pii p = g[curr][i];
      int next = p.first, cost = p.second;

      if(weight > cost)
        continue;

      if(next == N-1) {
        ans = max(ans, cost);
        continue;
      }

      if(dist[next] <= cost)
        continue;

      dist[next] = cost;

      pq.push(make_pair(cost, next));
    }
  }

  cout << (ans == -1 ? -1 : ans) << endl;

  return 0;
}