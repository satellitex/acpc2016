#include <bits/stdc++.h>

using namespace std;

#define INF (1LL<<55)
typedef vector<double> vec;
typedef vector<vec> mat;


int main()
{
    int L, d;
    double p;
    cin >> L >> p >> d;
    vector<double> S(L);
    vector<int> c(d);
    for (int i = 0; i < L; i++) {
        cin >> S[i];
    }
    for (int i = 0; i < d; i++) {
        cin >> c[i];
    }
    
    mat cost(L+1, vec(L+1));
    for (int i = 0; i < L; i++) {
        double sumS = 0;
        for (int j = i; j < L; j++) {
            sumS += S[j];
            cost[i][j+1] = p * (j - i + 1) / sumS;
        }
    }
    
    mat dp(d+1, vec(L+1, INF));
    dp[0][0] = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < d; j++) {
            if (dp[j][i] == INF) continue;
            dp[j][i+1] = min(dp[j][i+1], dp[j][i]);
            int next = i + c[j];
            if (next <= L) {
                dp[j+1][next] = min(dp[j+1][next],
                                    dp[j][i] + cost[i][next]);
            }
        }
    }
    printf("%.15f\n", *min_element(dp[d].begin(), dp[d].end()));   
    return 0;
}
