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

int N;

vector<bool> make_on_diameter(Graph& g, int curr, int prev, int s, int t, vector<int>& path) {

  path.push_back(curr);

  if(curr == t) {
    vector<bool> on_diameter(N);
    for(auto p: path)
      on_diameter[p] = 1;
    return on_diameter;
  }

  for(int next: g[curr]) {
    if(next == prev)
      continue;
    auto r = make_on_diameter(g, next, curr, s, t, path);
    if(!r.empty())
      return r;
  }

  return {};
}

vector<pair<int, int>> distances_to_diameter(Graph& g, vector<bool> const& on_diameter) {

  queue<int> q;
  vector<pair<int, int>> dists(N, make_pair(-1, -1)); // 距離, diameterのパスとの接点

  for(int i=0; i<N; i++) {
    if(on_diameter[i]) {
      q.push(i);
      dists[i] = make_pair(0, i);
    }
  }

  while(!q.empty()) {
    int from = q.front(); q.pop();
    for(int to: g[from]) {
      if(dists[to].first >= 0)
        continue;
      dists[to].first = dists[from].first + 1;
      dists[to].second = dists[from].second;
    }
  }

  return dists;
}

vector<int> distances_to_farthest_point(Graph& g, int s, int t, int diameter_len, vector<bool>& on_diameter) {

  queue<pair<int, int>> q;
  q.emplace(0, s);

  vector<int> dists(N, -1);
  dists[s] = diameter_len;

  while(!q.empty()) {
    int weight, curr; tie(weight, curr) = q.front(); q.pop();
    for(int next: g[curr]) {
      if(!on_diameter[next])
        continue;
      if(dists[next] >= 0)
        continue;
      q.emplace(weight + 1, next);
      dists[next] = max(weight + 1, diameter_len - (weight + 1));
    }
  }

  return dists;
}

int main() {

  cin >> N;

  vector<vector<int>> g(N);

  rep(i, N-1) {
    int u, v; cin >> u >> v;
    u --, v --;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int dlen, s, t; tie(dlen, s, t) = tree::diameter::diameter(g);

  vector<int> path;
  auto on_diameter = make_on_diameter(g, s, -1, s, t, path);
  auto dists = distances_to_diameter(g, on_diameter);
  auto long_lens = distances_to_farthest_point(g, s, t, dlen, on_diameter);

  rep(i, N)
    cout << 2 * N - 2 - dists[i].first - long_lens[dists[i].second] << endl;
  
  return 0;
}