#include <bits/stdc++.h>
using namespace std;

int main() {

  int N, M; cin >> N >> M;
  vector<vector<pair<int, int>>> g(N);

  for(int i=0; i<M; i++) {
    int a, b, c; scanf("%d%d%d", &a, &b, &c); a--, b--;
    g[a].push_back(make_pair(b, c));
  }
  
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.emplace(0, 0);

  vector<int> dist(N, 2e9);
  dist[0] = 0;

  int ans = -1;

  while(!pq.empty()) {
    auto p = pq.top(); pq.pop();
    int weight = p.first, curr = p.second;
    if(dist[curr] < weight) continue;

    for(auto p: g[curr]) {
      int next = p.first, cost = p.second;
      if(weight > cost) continue;
      if(next == N-1) {
        ans = max(ans, cost);
        continue;
      }
      if(dist[next] <= cost) continue;
      dist[next] = cost;
      pq.emplace(cost, next);
    }
  }
  cout << (ans == -1 ? -1 : ans) << endl;
  return 0;
}