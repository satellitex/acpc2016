#include<bits/stdc++.h>
using namespace std;
int N,M,L;
int dp[10][10][355];
typedef pair<int,int> P;
vector<P> T[10][10];

int solve(int y,int n,int l){
  int &ret = dp[y][n][l];
  if( ret != -1 ) return ret;
  if( l == L ) return ret = 0;
  if( y == 5 ) return ret = 0;
  if( n == N ) return ret = solve(y+1,0,l);
  ret = solve( y, n+1, l );
  for( P t : T[y][n] ){
    int nc = t.first, to = t.second;
    ret = max( ret, solve( y, to, l+1 ) + nc );    
  }
  return ret;
}

int main(){
  memset( dp,-1,sizeof( dp ) );
  cin >> N >> M >> L;
  for(int i=0;i<M;i++){
    int d,a,k,t;
    cin >> d >> a >> k >> t; --a;
    T[d][a].push_back( P( t, a + k ) );
  }
  cout << solve(0,0,0) << endl;
}
