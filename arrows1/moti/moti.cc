#include <bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i=a;i<(int)b;i++)
#define rep(i,n) REP(i,0,n)
#define all(c) (c).begin(), (c).end()
#define zero(a) memset(a, 0, sizeof a)
#define minus(a) memset(a, -1, sizeof a)
#define watch(a) { cout << #a << " = " << a << endl; }
template<class T1, class T2> inline bool minimize(T1 &a, T2 b) { return b < a && (a = b, 1); }
template<class T1, class T2> inline bool maximize(T1 &a, T2 b) { return a < b && (a = b, 1); }

typedef long long ll;
int const inf = 1<<29;

int N, M, L;
int D[303], A[303], K[303], T[303];
vector<int> g[303];
int dp[303][303];

int solve(int curr, int l) {
  if(l == L) return 0;
  int& ret = dp[curr][l];
  if(ret + 1) return ret;
  ret = 0;
  for(int to: g[curr])
    ret = max(ret, solve(to, l + 1) + T[to]);
  return ret;
}

int main() {

  cin >> N >> M >> L;

  rep(i, M) {
    cin >> D[i] >> A[i] >> K[i] >> T[i];
  }

  rep(i, M) rep(j, M) {
    if(D[i] > D[j])
      continue;
    if(D[i] == D[j] && A[i] + K[i] > A[j])
      continue;
    g[i].push_back(j);
  }

  rep(i, M)
    g[M].push_back(i);

  rep(i, 303) rep(j, 303)
    dp[i][j] = -1;

  cout << solve(M, 0) << endl;
  
  return 0;
}