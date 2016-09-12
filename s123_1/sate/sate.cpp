#include<bits/stdc++.h>
using namespace std;


struct edge{
  int to,c;
  edge(){}
  edge(int to,int c):to(to),c(c){}  
};

struct state{
  int id, pr, pf, f, r, sc;
  bool operator<(const state& e) const {
    return sc < e.sc;
  } 
};

int N,M,R;
int D[50];
vector<edge> G[50];

int H[35][35][2][2][1111];
int ans = 0;
priority_queue<state> q;
void update(int id, int pr, int pf, int f, int r, int sc){
  if( r > R ) return;
  if( id == N-1 ) ans = max( sc, ans );
  if( H[id][pr][pf][f][r] < sc ){
    H[id][pr][pf][f][r] = sc;
    q.push( (state){ id, pr, pf, f, r, sc } );
  }
}

int solve(){
  memset( H, -1, sizeof( H ) );

  q.push( (state){ 0, 0, 0, 1, 0, D[0] } );
  H[0][0][0][1][0] = D[0];
  
  while( !q.empty() ){
    state p = q.top(); q.pop();    
    //    cout << p.id << " "  << p.pr << " " << p.pf << " " << p.f << " " << p.r << " " << p.sc << endl;
    if( H[p.id][p.pr][p.pf][p.f][p.r] > p.sc ) continue;
    for( edge e : G[p.id] ){     
      int nc = p.sc + D[e.to];
      int nr = p.r + e.c;
      if( p.pf && e.to == p.pr ){
        if( e.c * 2 < 15 ) {
          update( e.to, p.id, 0, 1, p.r + 15 - e.c, nc );
          nc = p.sc;
        }
      }
      if( nc>p.sc ){
        update( e.to, p.id, p.f, 1, nr, nc );
      }
      else
        update( e.to, p.id, p.f, 0, nr, nc );
    }
    update( p.id, p.id, p.f, 1, p.r+15, p.sc + D[p.id] );
  }
  return ans;
}

int main(){
  cin >> N >> M >> R;
  for(int i=0;i<N;i++) cin >> D[i];
  for(int i=0;i<M;i++){
    int a,b,c; cin >> a >> b >> c; --a; --b;
    G[a].push_back( edge( b, c ) );
    G[b].push_back( edge( a, c ) );
  }
  cout << solve() << endl;
}
