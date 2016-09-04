#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m, n, o, p, c;
    cin >> m >> n >> o >> p;
    int a, b;
    vector< vector<int> > cnt(n, vector<int>(m));
    for (int i = 0; i < p; i++) {
        cin >> a >> b >> c;
        cnt[b][a]++;
    }
    
    int s, res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> s;
            if (s == 0) continue;
            res += cnt[i][j];
        }
    }
    cout << res << endl;
    return 0;
}
