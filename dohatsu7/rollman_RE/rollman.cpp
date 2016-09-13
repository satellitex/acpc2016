#include <bits/stdc++.h>
using namespace std;
#define NMAX 5000
#define MMAX 100000
#define AGE_INF 10000000
int N, M;
int used[NMAX];
vector< vector< pair<int, int> > > node; //node[to] = [(age, from)]

bool func(int v, int age){
    if(v == 0) return true;

    used[v] = true;
    bool res = false;
    for(int i = 0; i < node[v].size(); i++){
        int nextv = node[v][i].second;
        int nextage = node[v][i].first;
        if(used[nextv] == true) continue;
        if(age >= nextage){
            bool f = func(nextv, nextage);
            if(f == true){
                res = true;
                break;
            }
        }
    }
    used[v] = false;
    return res;
}

int main(void){
    memset(used, 0, NMAX*sizeof(int));
    cin >> N >> M;
    node = vector< vector< pair<int, int> > >(N);
    for(int i = 0; i < M; i++){
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        node[b].push_back( make_pair(c, a) );
    }
    for(int i = 0; i < N; i++){
        sort(node[i].begin(), node[i].end(), greater< pair<int, int> >());
    }

    for(int i = 0; i < node[N-1].size(); i++){
        bool f = func(node[N-1][i].second, node[N-1][i].first);
        if(f == true){
            cout << node[N-1][i].first << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}
