#include <bits/stdc++.h>

using namespace std;

#define MAX_N 5000
const int INF = (1<<29);

struct Edge {
    int to, age;
    Edge (int to, int age) :
        to(to), age(age) {}
};

struct State {
    int c, v, max_age;
    State (int c, int v, int max_age) :
        c(c), v(v), max_age(max_age) {}

    bool operator < (const State &s) const {
        return c > s.c;
    }
};

int main()
{
    int N, M, a, b, c;
    cin >> N >> M;
    
    vector<Edge> G[MAX_N];
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c; a--; b--;
        G[a].push_back(Edge(b, c));
    }
    
    vector<int> d(MAX_N + 1, INF);
    d[0] = 1;

    priority_queue<State> pq;
    pq.push(State(1, 0, 1));
    int res = -1;
    
    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (s.v == N-1 || d[s.v] < s.c) continue;
        
        for (int i = 0; i < (int)G[s.v].size(); i++) {
            Edge &e = G[s.v][i];
            if (e.to == N-1 && s.max_age <= e.age) {
                res = max(res, e.age);
            }
                
            if (s.max_age <= e.age && e.age < d[e.to]) {
                d[e.to] = e.age;
                pq.push(State(d[e.to], e.to, e.age));
            }
        }
    }
    cout << res << endl;
    return 0;
}
