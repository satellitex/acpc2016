#include<bits/stdc++.h>
using namespace std;
struct state{
  int id, pr, r, sc;
  bool operator<(const state& e) const {
    return sc < e.sc;
  } 
};

int N,M,R;
int D[50];
const int INF = (1<<29);
int H[35][35][1111];
int W[35][35];
int ans = 0;
queue<state> q;
void update(int id, int pr, int r, int sc){
  if( r > R ) return;
  if( H[id][pr][r] < sc ){
    H[id][pr][r] = sc;
    q.push( (state){ id, pr, r, sc } );
  }
}

int solve(){
  memset( H, -1, sizeof( H ) );
  q.push( (state){ 0, 0, 0, D[0] } );
  H[0][0][0] = D[0];
  while( !q.empty() ){
    state p = q.front(); q.pop();
    if( H[p.id][p.pr][p.r] > p.sc ) continue;
    for(int i=0;i<N;i++){
      int nsc = p.sc + D[i];
      int nr = p.r + W[p.id][i];      
      if( i == p.pr || i == p.id )
        if( 15 > W[p.id][i] * 2 ){
          update( i, i, p.r + 15 - W[p.id][i], nsc );
          continue;
        }
      update( i, p.id, nr, nsc );      
    }
  }
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      for(int k=0;k<=R;k++)
        if( W[i][N-1] + k <= R )
          ans = max( ans, H[i][j][k] );      
  return ans;
}

int main(){
  cin >> N >> M >> R;
  for(int i=0;i<N;i++) cin >> D[i];
  fill( W[0], W[35], INF );  
  for(int i=0;i<M;i++){
    int a,b,c; cin >> a >> b >> c; --a; --b;
    W[a][b] = W[b][a] = c;
  }
  for(int i=0;i<N;i++) W[i][i] = W[i][i] = 0;
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      for(int k=0;k<N;k++)
        W[j][k] = min( W[j][k], W[j][i]+W[i][k] );
  cout << solve() << endl;
}
