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
    switch (K) {
        case 1: {
            for (int i = 0; i < N; i++) {
                int m = M - min(b[i], M);
                int c1 = a[i] * min(b[i], M);
                res = max(res, c1 + m);
            }                
            break;
        }
        case 2: {
            for (int i = 0; i < N; i++) {
                int m = M - min(b[i], M);
                int c1 = a[i] * min(b[i], M);
                for (int j = 0; j < N; j++) {
                    if (i == j) continue;
                    int n = m - min(b[j], m);
                    int c2 = a[j] * min(b[j], m);
                    res = max(res, c1 + c2 + n);
                }
            }                
            break;
        }
        case 3: {
            for (int i = 0; i < N; i++) {
                int m = M - min(b[i], M);
                int c1 = a[i] * min(b[i], M);
                for (int j = 0; j < N; j++) {
                    if (i == j) continue;
                    int n = m - min(b[j], m);
                    int c2 = a[j] * min(b[j], m);
                    for (int k = 0; k < N; k++) {
                        if (i == k || j == k) continue;
                        int o = n - min(b[k], n);
                        int c3 = a[k] * min(b[k], n);
                        res = max(res, c1 + c2 + c3 + o);
                    }
                }
            }
            break;
        }
        default:
            assert(0);
    }
    cout << res << endl;
    return 0;
}
