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

namespace tree { namespace diameter {

  using Weight  = ll;
  using Edge    = int;
  using Graph   = vector<vector<Edge>>;

  namespace detail {
    using Result = pair<Weight, int>;

    Result visit(int parent, int curr, Graph const& G) {
      Result ret(0, curr);
      for(auto && to: G[curr]) {
        if(to == parent) { continue; }
        auto t = visit(curr, to, G);
        t.first += 1;
        if(ret.first < t.first) { ret = t; }
      }
      return ret;
    }
  }

  using Result = tuple<Weight, int, int>;

  Result diameter(Graph const& G) {
    auto r = detail::visit(-1, 0, G);
    auto t = detail::visit(-1, r.second, G);
    return Result{t.first, r.second, t.second};
  }

#define USE_TREE_DIAMETER   \
  using tree::diameter::Weight; \
  using tree::diameter::Edge;   \
  using tree::diameter::Graph;  \
  using tree::diameter::diameter;
}}

USE_TREE_DIAMETER

int main() {

  int N; cin >> N;

  vector<vector<int>> g(N);

  rep(i, N-1) {
    int u, v; scanf("%d%d", &u, &v);
    u --, v --;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int dlen, s, t; tie(dlen, s, t) = tree::diameter::diameter(g);

  int starts[2] = {s, t};
  vector<vector<int>> dist(2, vector<int>(N, -1));

  rep(i, 2) {
    queue<int> q;
    q.push(starts[i]);
    dist[i][starts[i]] = 0;

    while(!q.empty()) {
      int curr = q.front(); q.pop();
      for(int next: g[curr]) {
        if(dist[i][next] >= 0) continue;
        dist[i][next] = dist[i][curr] + 1;
        q.push(next);
      }
    }
  }

  rep(i, N)
    cout << 2 * N - 2 - max(dist[0][i], dist[1][i]) << endl;
  
  return 0;
}