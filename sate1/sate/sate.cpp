#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
vector<int> G[100005];
int N;
int K[100005];

P dfs(int id,int pr,int f){
  P ret = P(f,id);
  K[id] = max( K[id], f );
  for( int to : G[id] ){
    if( to == pr ) continue;
    ret = max( ret, dfs( to, id, f + 1 ) );
  }
  return ret;
}

P gethz(){
  P p = dfs(1,1,0);
  P c = dfs(p.second,p.second,0);
  return P( p.second, c.second );
}


void solve(){
  P r = gethz();
  memset( K, 0, sizeof( K ) );
  dfs( r.first, r.first, 0 );
  dfs( r.second, r.second, 0 );
  for(int i=1;i<=N;i++) cout << (N-1)*2 - K[i] << endl;
}

int main(){
  cin >> N;
  for(int i=0;i<N-1;i++){
    int u,v; cin >> u >> v;
    G[u].push_back( v ); G[v].push_back( u );
  }
  solve();
}

