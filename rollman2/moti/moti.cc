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

int nabe[55][55][55];
bool ami[55][55];

int main() {

  int X, Y, Z; cin >> X >> Y >> Z;
  int P; cin >> P;

  rep(i, P) {
    int a, b, c; cin >> a >> b >> c;
    nabe[c][b][a]++;
  }

  rep(i, Y) rep(j, X)
    cin >> ami[i][j];

  int ans = 0;

  rep(i, Z) rep(j, Y) rep(k, X)
    if(ami[j][k])
      ans += nabe[i][j][k];

  cout << ans << endl;
  
  return 0;
}