#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M, L, d;
    cin >> N >> M >> L;
    vector<int> a(M), b(M), t(M);
    for (int i = 0; i < M; i++) {
        cin >> d >> a[i] >> b[i] >> t[i];
        a[i] = a[i] + d * N - 1;
        b[i] = a[i] + b[i];
    }
    
    int res = 0;
    vector<vector<int>> dp(N * 5 + 1, vector<int>(L + 1));
    for (int i = 0; i <= N * 5; i++) {
        for (int j = 0; j < L; j++) {
            for (int k = 0; k < M; k++) {
                if (i <= a[k]) {
                    dp[b[k]][j+1] = max(dp[b[k]][j+1], dp[i][j] + t[k]);
                    res = max(res, dp[b[k]][j+1]);
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}
