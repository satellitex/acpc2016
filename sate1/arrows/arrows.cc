#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vec;
typedef vector<vec> Graph;
typedef pair<int, int> pii;
const int INF = 1e9;

vec bfs(set<int> &s, Graph &G)
{
    vec dist(G.size(), INF);
    queue<pii> que; 
    for (auto &x: s) {
        dist[x] = 0;
        que.push(pii(0, x));    
    }
        
    while (!que.empty()) {
	pii p = que.front(); que.pop();
	int v = p.second;
	for (int i = 0; i < (int)G[v].size(); i++) {
	    int to = G[v][i];
	    if (dist[v] + 1 < dist[to]) {
		dist[to] = dist[v] + 1;
		que.push(pii(dist[to], to));                
	    }
	}
    }
    return dist;
}

int get_farthest_point(int v, Graph &G)
{
    set<int> st = {v};
    vec vec = bfs(st, G);
    int resv = -1, max = -1;
    for (int i = 0; i < (int)G.size(); i++) {
	if (max < vec[i]) {
	    max = vec[i];
	    resv = i;
	}
    }
    return resv;
}

set<int> res;

void dfs(int v, int prev, int target, set<int> &td, Graph &G)
{
    td.insert(v);
    if (v == target) {
        res = td;
        return;
    }    
    for (int i = 0; i < (int)G[v].size(); i++) {
        int to = G[v][i];
        if (to == prev) continue;
        dfs(to, v, target, td, G);
    }
    td.erase(v);
}

void solve(Graph &G)
{
    int N = G.size();
    int v0 = 0;
    int v1 = get_farthest_point(v0, G);
    int v2 = get_farthest_point(v1, G);
    set<int> td, st1 = {v1}, st2 = {v2};
    dfs(v1, -1, v2, td, G);

    int cost = 0;
    for (int i = 0; i < N; i++) {
        if (!res.count(i)) {
            cost += 2;
        }
    }
    vec d1 = bfs(st1, G), d2 = bfs(st2, G), d3 = bfs(res, G);
    for (int i = 0; i < N; i++) {
        printf("%d\n", d2[v1] + min(d1[i], d2[i]) + cost - 2 * d3[i]);
    }
}

int main()
{   
    int N, u, v;
    scanf("%d", &N);
    Graph G(N);
    for (int i = 0; i < N-1; i++) {
        scanf("%d %d", &u, &v); u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    solve(G);
    return 0;
}
