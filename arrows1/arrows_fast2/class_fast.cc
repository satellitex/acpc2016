#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1<<13);
typedef pair<int, int> pii;
typedef pair<pii, int> P;

int n, dat[2][2*MAX_N-1];
  
void init(int n_)
{
    n = 1;
    while (n < n_) n *= 2;
    fill(dat[0], dat[2], 0);
}
  
void update(int k, int a, int L)
{
    k += n - 1;
    dat[L][k] = max(dat[L][k], a);
    while (k > 0) {
	k = (k - 1) / 2;
	dat[L][k] = max(dat[L][k * 2 + 1], dat[L][k * 2 + 2]);
    }
}

int query(int a, int b, int k, int l, int r, int L)
{
    if(r <= a || b <= l) {
        return 0;
    }
    if (a <= l && r <= b) {
	return dat[L][k];
    } else {
	int vl = query(a, b, k * 2 + 1, l, (l + r) / 2, L);
	int vr = query(a, b, k * 2 + 2, (l + r) / 2, r, L);        
	return max(vl, vr);
    }
}

int main()
{
    int N, M, L, d, a, b, s, t;
    cin >> N >> M >> L;
    vector<P> p(M);    
    for (int i = 0; i < M; i++) {
        cin >> d >> a >> b >> t;
        a = a + d * N;
        b = a + b - 1;
        p[i] = P(pii(b, a), t);
    }

    sort(p.begin(), p.end());
    init(5 * N);
    int res = 0;
    for (int i = 0; i < L; i++) {
        int curr = i & 1, next = ~i & 1;
        for (int j = 0; j < M; j++) {
            s = p[j].first.second; t = p[j].first.first;        
            int mx = query(0, s, 0, 0, n, curr);
            res = max(res, mx + p[j].second);
            update(t, mx + p[j].second, next);
        }
        fill(dat[curr], dat[curr] + 2*n-1, 0);
    }
    cout << res << endl;
    return 0;
}
