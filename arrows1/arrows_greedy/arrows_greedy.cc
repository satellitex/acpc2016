#include <bits/stdc++.h>

using namespace std;

struct P {
    int a, b, c;
    P () {}
    P (int a, int b, int c) :
        a(a), b(b), c(c) {}

    bool operator < (const P &p) const {
        if (c != p.c) {
            return c > p.c;
        } else if (b - a != p.b - p.a) {
            return (b - a < p.b - p.a);
        }
        return 0;
    }
};

int main()
{
    int N, M, L, d, a, k, t;
    cin >> N >> M >> L;
    vector<P> v;
    for (int i = 0; i < M; i++) {
        cin >> d >> a >> k >> t;
        a = a + d * N;
        v.push_back(P(a, a + k, t));
    }
    
    sort(v.begin(), v.end());
    int i = 0, l = 0, res = 0;
    vector<bool> used(N * 5 + 1);
    while (i < M && l < L) {
        bool ok = 1;
        for (int j = v[i].a; j < v[i].b; j++) {
            if (used[j]) {
                ok = 0;
                break;
            }
        }
        
        if (ok) {
            l++;
            for (int j = v[i].a; j < v[i].b; j++) {
                used[j] = 1;
            }
            res += v[i].c;           
        }
        i++;
    }
    cout << res << endl;
    return 0;
}
