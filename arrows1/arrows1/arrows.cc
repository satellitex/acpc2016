#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

void update(int &l, int r)
{
    if (l < r) l = r;
}

int main()
{
    int N, M, L, d, a, b, t;
    cin >> N >> M >> L;
    
    set<pii> p[5 * N + 1];
    for (int i = 0; i < M; i++) {
        cin >> d >> a >> b >> t;
        a = a + d * N;
        p[a].insert(pii(a + b, t));
    }
    N = 5 * N;
    int res = 0;
    vector<vector<int>> dp(L + 1, vector<int>(N + 2)); 
    for (int i = 0; i <= L; i++) {
        for (int j = 0; j <= N; j++) {
            update(dp[i][j+1], dp[i][j]);
            for (auto &x: p[j]) {
                b = x.first, t = x.second;
                if (i + 1 <= L) {
                    update(dp[i+1][b], dp[i][j] + t);                
                    update(res, dp[i+1][b]);
                }                
            }
        }
    }
    cout << res << endl;
    return 0;
}
