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

const int inf = 1 << 25;

int bfs()
{
  queue<int> que;
  vector<int> minEngy(N + 1, inf);
  que.push(0);  
  minEngy[0] = 1;

  int ret = -1;
  while(!que.empty()) {
    int now = que.front(); que.pop();
    if(now == N-1) continue;
    for(int i = 0; i < G[now].size(); i++) {
      edge e = G[now][i];
      if(e.cost >= minEngy[now]) {
	if(e.to == N-1) {
	  ret = max(ret, e.cost);
	}
	if(e.cost < minEngy[e.to]) {
	  que.push(e.to);
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
  
  cout << bfs() << endl;
  
  return 0;
}
