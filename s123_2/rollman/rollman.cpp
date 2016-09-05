/*
 *  こ れ は む ず い
 */

#include <bits/stdc++.h>
using namespace std;

int N, M, K;
pair<int, int> a[15];
int memo[20][20000][3];

int func(int bank, int poss, int k){
    if(memo[bank][poss][k] != -1) return memo[bank][poss][k];
    if(bank == N || poss <= 0 || k == K) return poss;
    int res = func(bank+1, poss, k);
    for(int pay = 1; pay <= min(a[bank].second, poss); pay++){
        res = max(res, func(bank+1, poss - pay, k+1) + pay*a[bank].first);
    }
    return memo[bank][poss][k] = res;
}

int main(void){
    cin >> N >> M >> K;
    for(int i = 0; i < 20; i++) for(int j = 0; j < 20000; j++) for(int k = 0; k < 3; k++) memo[i][j][k] = -1;
    for(int i = 0; i < N; i++) cin >> a[i].first;
    for(int i = 0; i < N; i++) cin >> a[i].second;

    cout << func(0, M, 0) << endl;

    return 0;
}
