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

typedef pair<int, int> pii;

int N, M, K;
int a[15], b[15];

int solve(int idx, int m, bitset<15>& bs) {
  if(idx == K)
    return m;

  int ret = 0;

  for(int i=0; i<N; i++) {
    if(bs[i]) continue;
    bs[i] = 1;
    int prod = min(m, b[i]);
    ret = max(ret, solve(idx + 1, m - prod, bs) + a[i] * prod);
    bs[i] = 0;
  }

  return ret;
}

int main() {

  cin >> N >> M >> K;
  rep(i, N) cin >> a[i];
  rep(i, N) cin >> b[i];

  bitset<15> bs;
  cout << solve(0, M, bs) << endl;
  
  return 0;
}