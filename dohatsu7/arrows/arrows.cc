#include <bits/stdc++.h>

using namespace std;

#define MAX_N 100000
const int INF = INT_MAX;

struct Edge {
    int to, age;
    Edge (int to, int age) :
        to(to), age(age) {}
};

struct State {
    int c, v;
    State (int c, int v) :
        c(c), v(v) {}

    bool operator < (const State &s) const {
        return c > s.c;
    }
};

int main()
{
    int N, M, a, b, c;
    scanf("%d %d", &N, &M);
    
    vector<Edge> G[MAX_N];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &c); a--; b--;
        G[a].push_back(Edge(b, c));
    }
    
    vector<int> d(MAX_N + 1, INF);
    d[0] = 1;

    priority_queue<State> pq;
    pq.push(State(1, 0));
    int res = -1;
    
    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (s.v == N-1 || d[s.v] < s.c) continue;
        
        for (int i = 0; i < (int)G[s.v].size(); i++) {
            Edge &e = G[s.v][i];
            if (d[s.v] > e.age) continue;
            if (e.to == N-1) {
                res = max(res, e.age);
            }
                
            if (e.age < d[e.to]) {
                d[e.to] = e.age;
                pq.push(State(d[e.to], e.to));
            }
        }
    }
    printf("%d\n", res);
    return 0;
}
