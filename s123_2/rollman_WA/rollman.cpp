#include <bits/stdc++.h>
using namespace std;

int N, M, K;
pair<int, int> a[15];

int main(void){
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++) cin >> a[i].first;
    for(int i = 0; i < N; i++) cin >> a[i].second;

    sort(a, a+N, greater<pair<int, int> >());

    for(int i = 0; i < N; i++) cout << a[i].first << " " << a[i].second << endl;

    int idx = 0;
    int ans = 0;
    while(idx < K && M > 0){
        ans += min(M, a[idx].second) * a[idx].first;
        M -= a[idx].second;
        idx++;
    }

    cout << ans << endl;

    return 0;
}
