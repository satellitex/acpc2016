#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> P;

struct edge {
  int to, cost;
  edge(){}
  edge(int to, int cost):to(to), cost(cost){}
};

vector< vector<edge> > G;
int N, M;

const int inf = 1 << 30;

int dijkstra()
{
  priority_queue<P, vector<P>, greater<P> > que;
  vector<int> minEngy(N + 1, inf);
  que.push(P(1, 0));  
  minEngy[0] = 1;

  int ret = -1;
  while(!que.empty()) {
    P p = que.top(); que.pop();
    int now = p.second, engy = p.first;
    if(now == N-1 || engy > minEngy[now]) continue;
    for(int i = 0; i < G[now].size(); i++) {
      edge& e = G[now][i];
      if(e.cost >= minEngy[now]) {
	if(e.to == N-1) {
	  ret = max(ret, e.cost);
	}
	if(e.cost < minEngy[e.to]) {
	  que.push(P(e.cost, e.to));
	  minEngy[e.to] = e.cost;
	}
      }
    }
  }
  return ret;
}

int main()
{
  cin >> N >> M;
  G.resize(N + 1);
  for(int i = 0; i < M; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    G[a].push_back(edge(b, c));
  }
  
  cout << dijkstra() << endl;
  
  return 0;
}
