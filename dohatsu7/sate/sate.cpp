#include<bits/stdc++.h>
using namespace std;

int N,M;
struct edge {
  int to,c;
  edge(){}
  edge(int to,int c):to(to),c(c){}
  bool operator<(const edge &e ) const {
    return c > e.c;
  }
};
vector<edge> G[100005];
int H[100005];
const int INF = INT_MAX;
int solve(){
  fill( H, H+N+1, INF );
  priority_queue<edge> q;
  H[1] = 1;
  q.push( edge(1,1) );
  int res = -1;
  while( !q.empty() ){
    edge p = q.top(); q.pop();
    if( H[ p.to ] < p.c ) continue; 
    for( edge e : G[p.to] ){
      if( p.c <= e.c ){
        if( e.to == N ) res = max( res, e.c );
        if( H[e.to] > e.c ){
          H[e.to] = e.c;
          q.push( edge( e.to, e.c ) );
        }
      }
    }
  }
  return res;
}

int main(){
  cin >> N >> M;
  for(int i=0;i<M;i++){
    int a,b,c;
    cin >> a >> b >> c;
    G[a].push_back( edge( b, c ) );
  }
  cout << solve() << endl;
}
