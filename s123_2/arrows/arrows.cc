#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }
    
    int res = 0;
    for (int i = 0; i < N; i++) {
        int m = M - min(b[i], M);
        int c1 = a[i] * min(b[i], M);
        res = max(res, c1 + m);
        for (int j = 0; j < N; j++) {
            if (i == j || K == 1) continue;
            int n = m - min(b[j], m);
            int c2 = a[j] * min(b[j], m);
            res = max(res, c1 + c2 + n);
            for (int k = 0; k < N; k++) {
                if (i == k || j == k || K == 2) continue;
                int o = n - min(b[k], n);
                int c3 = a[k] * min(b[k], n);
                res = max(res, c1 + c2 + c3 + o);
            }
        }
    }       
    cout << res << endl;
    return 0;
}
