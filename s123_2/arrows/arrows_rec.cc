#include <bits/stdc++.h>

using namespace std;

int rec(int S, int N, int K, int money,
        vector<int> &a, vector<int> &b)
{
    if (__builtin_popcount(S) == K) return money;
    int res = 0;
    for (int i = 0; i < N; i++) {
        if (S >> i & 1) continue;
        int m = min(b[i], money);
        res = max(res,
                  rec(S | (1<<i), N, K, money - m, a, b) + a[i] * m);
    }
    return res;
}

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
    cout << rec(0, N, K, M, a, b) << endl;
    return 0;
}
