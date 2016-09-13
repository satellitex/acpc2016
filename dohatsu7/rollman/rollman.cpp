#include <bits/stdc++.h>
using namespace std;
#define NMAX 100000
#define MMAX 200000
#define AGE_INF INT_MAX
int N, M;
int used[NMAX];
int d[NMAX];
vector< vector< pair<int, int> > > node; //


int main(void){
    memset(used, 0, NMAX*sizeof(int));
    memset(d, 0, NMAX*sizeof(int));
    for(int i = 0; i < NMAX; i++) d[i] = AGE_INF;
    cin >> N >> M;
    node = vector< vector< pair<int, int> > >(N);
    for(int i = 0; i < M; i++){
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        node[a].push_back( make_pair(c, b) );
    }

    d[0] = 1;
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > que;
    que.push(make_pair(1, 0));

    while(!que.empty()){
        pair<int, int> q = que.top(); que.pop();
        int age = q.first;
        int from = q.second;
        if(used[from]) continue;
        used[from] = true;
        for(int i = 0; i < node[from].size(); i++){
            int nextage = node[from][i].first;
            int to = node[from][i].second;
            if(nextage >= age){
                que.push(make_pair(nextage, to));
                d[to] = min(d[to], nextage);
            }
        }
    }

    if(d[N-1] == AGE_INF){
        cout << -1 << endl;
        return 0;
    }else{
        int ans = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < node[i].size(); j++){
                if(node[i][j].second == N-1 && node[i][j].first >= d[i]){
                    ans = max(ans, node[i][j].first);
                }
            }
        }
        cout << ans << endl;
    }
}
