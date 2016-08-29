#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1<<13);
const int MAX_L = (1<<10);
typedef pair<int, int> pii;
typedef pair<pii, int> P;

int n, dat[2*MAX_N-1][MAX_L+1];
  
void init(int n_, int L)
{
    n = 1;
    while (n < n_) {
        n *= 2;
    }
    for (int i = 0; i < 2*n-1; i++) {
	for (int j = 0; j <= L; j++) {
            dat[i][j] = 0;        
        }
    }
}
  
void update(int k, int a, int L)
{
    k += n - 1;
    dat[k][L] = max(dat[k][L], a);
    while (k > 0) {
	k = (k - 1) / 2;
	dat[k][L] = max(dat[k * 2 + 1][L], dat[k * 2 + 2][L]);
    }
}

int query(int a, int b, int k, int l, int r, int L)
{
    if(r <= a || b <= l) {
        return 0;
    }
    if (a <= l && r <= b) {
	return dat[k][L];
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
    init(5 * N, L);
    int res = 0;
    for (int i = 0; i < M; i++) {
        s = p[i].first.second; t = p[i].first.first;
        for (int j = 0; j < L; j++) {
            int mx = query(0, s, 0, 0, n, j);
            res = max(res, mx + p[i].second);
            update(t, mx + p[i].second, j+1);
        }
    }
    cout << res << endl;
    return 0;
}
