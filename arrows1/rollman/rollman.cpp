#include <bits/stdc++.h>
using namespace std;
#define NMAX 300
#define MMAX 300
#define INF (INT_MAX/10)
int N, M, L;
int d[MMAX], a[MMAX], k[MMAX], t[MMAX];
int memo[NMAX*5*10][MMAX*10];
vector< vector< pair<int, int> > > classes;   //class[begin] = (end, credits)

int func(int period, int enrolled){
    if(memo[period][enrolled] != -1) return memo[period][enrolled];
    int date = period / N;
    if(date >= 5 || enrolled == L){
        return 0;
    }
    int res = func(period+1, enrolled);
    for(int i = 0; i < classes[period].size(); i++){
        int next = period + classes[period][i].first;
        res = max(res, func(next, enrolled+1) + classes[period][i].second);
    }
    return memo[period][enrolled] = res;
}

int main(void){
    cin >> N >> M >> L;
    classes.resize(N*5);
    for(int i = 0; i < NMAX*5*10; i++) for(int j=0; j < MMAX*10; j++) memo[i][j] = -1;
    for(int i = 0; i < M; i++) cin >> d[i] >> a[i] >> k[i] >> t[i];
    for(int i = 0; i < M; i++){
        a[i]--;
        classes[N*d[i] + a[i]].push_back(make_pair(k[i], t[i]));
    }
    cout << func(0, 0) << endl;
    return 0;
}
