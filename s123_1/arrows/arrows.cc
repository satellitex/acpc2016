#include <bits/stdc++.h>

using namespace std;

#define MAX_N 30
#define MAX_R 1000
#define INF (1<<29)

void update(int &l, int r)
{
    if (l < r) l = r;
}

int main()
{
    int N, M, R;
    cin >> N >> M >> R;
    vector<int> ball(N);
    for (int i = 0; i < N; i++) {
	cin >> ball[i];
    }
    int d[MAX_N][MAX_N];
    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    d[i][j] = (i != j) * INF;
	}
    }
    int a, b, c;
    for (int i = 0; i < M; i++) {
	cin >> a >> b >> c; a--; b--;
	d[a][b] = d[b][a] = c;
    }

    for (int k = 0; k < N; k++) {
	for (int i = 0; i < N; i++) {
	    for (int j = 0; j < N; j++) {
		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	    }
	}
    }
    
    int res = 0;
    int dp[MAX_R+1][MAX_N][MAX_N];
    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;    
    
    for (int i = 0; i <= R; i++) {
        for (int prev = 0; prev < N; prev++) {
            for (int curr = 0; curr < N; curr++) { 
                if (dp[i][curr][prev] == -1 || i + d[curr][N-1] > R) continue;
                if (i + 15 <= R) update(dp[i+15][curr][curr],
                                        dp[i][curr][prev] + ball[curr]);
                if (curr == N-1) update(res, dp[i][curr][prev]);
                for (int next = 0; next < N; next++) {
                    if (curr == next) continue;
                    if (prev == next) {
                        if (2 * d[prev][curr] >= 15) {
                            int ni = i + d[prev][curr];
                            if (ni <= R) {
                                update(dp[ni][next][prev],
                                       dp[i][curr][prev] + ball[next]);
                            } 
                        } else {
                            int ni = i + (15 - d[prev][curr]);
                            if (ni <= R) {
                                update(dp[ni][next][prev],
                                       dp[i][curr][prev] + ball[next]);
                            } 
                        }
                    } else {
                        int ni = i + d[curr][next];                        
                        if (ni <= R) {
                            update(dp[ni][next][curr], dp[i][curr][prev] + ball[next]);
                        }
                    }
                }
            }
        }
    }
    cout << res << endl;
    return 0;
}
