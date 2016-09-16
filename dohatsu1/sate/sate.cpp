#include<bits/stdc++.h>
using namespace std;

const int MAX_V = 10222;
const int INF = 1<<29;
struct edge{int to,cap,rev;};
struct Edge{
  int u,v;
  string s;
  bool operator<(const Edge &e) const {
    return s < e.s;
  }
  bool operator==(const Edge &e) const {
    return s == e.s;
  }
};

vector<edge> G[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to, int cap){
  G[from].push_back((edge){to, cap, (int)G[to].size()});
  G[to].push_back((edge){from, 0, (int)G[from].size()-1});
}

int dfs(int v, int t, int f){
  if(v == t)return f;
  used[v] = true;
  for(int i = 0 ; i < (int)G[v].size() ; i++){
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0){
      int d = dfs(e.to,t,min(f,e.cap));
      if(d > 0){	
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow(int s,int t){
  int flow = 0;
  for(;;){
    memset(used,0,sizeof(used));
    int f = dfs(s,t,INF);
    if(f == 0)return flow;
    flow += f;
  }
}

int S,T;
int once_flow(int s,int t){
  memset(used,0,sizeof(used));
  return dfs(s,t,INF);
}

int remove_flow(edge &u,edge &v){
  bool f = false;
  if( u.cap == 0 ) f = true;
  u.cap = 0;
  v.cap = 0;
  if( f ){
    int fw = once_flow(v.to,u.to);
    if( fw == 0 ) {
      once_flow(T,u.to);    
      once_flow(v.to,S);
      if( once_flow(S,T) == 1 ) return 0;
      return -1;
    }
    return 0;
  }
  return 0;
}

int add_flow(edge &u,edge &v){
  u.cap = 1;
  v.cap = 0;
  int ret =  once_flow(S,T);
  return ret;
}

char otoc(int n){
  if( 0 <= n && n <= 9 ) return n+'0';
  else return n + 'a' - 10;
}

int ctoo(char c){
  if( '0' <= c && c <= '9' ) return c - '0';
  else return c - 'a' + 10;
}

struct ox {
  vector<int> t;
  ox(string s){
    for(char c : s )
      t.push_back( ctoo(c) );
  }
  string str(){
    string s="";
    for(int c : t )
      s += otoc(c);    
    return s;
  }
  string down(){
    string s="";
    for(int c : t ){
      if( !(c & 1) ) c = (c+15)%16;
      s += otoc(c);
    }
    return s;
  }
  string up(){
    string s="";
    for(int c : t ){
      if( !(c & 1) ) c = (c+1)%16;
      s += otoc(c);
    }    
    return s;
  }
  bool isEven(){
    for( int c : t )
      if( !(c&1) ) return true;
    return false;
  }
  bool operator<(const ox& o) const {
    return t < o.t;
  }
  bool operator==(const ox& o) const {
    return t==o.t;
  }
};

bool check( ox &a, ox &b ){
  int n = a.t.size();
  bool on=false;
  for(int i=0;i<n;i++){
    if( a.t[i] != b.t[i] ){
      if( on ) return false;
      else if( ( a.t[i] + 2 ) % 16 == b.t[i] ||
          ( b.t[i] + 2 ) % 16 == a.t[i] ) on = true;
      else return false;
    }
  }
  return true;
}

string bwstr( ox& a, ox& b ){
  string s = "";  
  for(int i=0;i<(int)a.t.size();i++){
    if( a.t[i] != b.t[i] ) {
      if( (a.t[i] + 2)%16 == b.t[i] ) s += otoc( (a.t[i]+1)%16 );
      else s += otoc( (b.t[i]+1)%16 );
    } else s += otoc(a.t[i]);
  }
  return s;
}


int N;
vector<int> D[MAX_V];
int Enum[MAX_V];
int W[MAX_V];
void nuri(int id,int n){
  if( ~W[id] ) return;  
  W[id] = n;
  for( int to : D[id] )
    nuri( to, 1-n );
  return;
}

int main(){
  cin >> N;
  vector<ox> vs;
  map<string,int> mp;
  for(int i=0;i<N;i++){
    string s; cin >> s;
    mp[s] = 1;
    ox m = ox( s );
    ox p = ox( s );    
    vs.push_back( ox(m.down()) );
    vs.push_back( ox(m.up()) );
  }
  vector<Edge> E;
  sort( vs.begin(), vs.end() );
  vs.erase( unique( vs.begin(), vs.end() ), vs.end() );
  
  N = vs.size();
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      if( i != j )
        if( check( vs[i], vs[j] ) )
          if( mp.count( bwstr( vs[i], vs[j] ) ) )
            D[i].push_back( j );
  memset( W, -1, sizeof( W ) );
  
  vector<string> res;
  int ans = 0;
  S = N,T=N+1;
  
  ans += N;
  for(int i=0;i<N;i++){
    if( W[i]==-1 ) nuri( i, 0 );
    if( W[i] == 0 ) {
      for( int to : D[i] )
        E.push_back( (Edge){ i, to, bwstr( vs[i], vs[to] ) } );
      add_edge( S, i, 1 );
    } else
      add_edge( i, T, 1 );
  }

  for( Edge e : E ){
    add_edge( e.u, e.v, 1 );
  }

  ans = max_flow(S,T);  
  cout << ans << endl;

  int n = E.size();
  for(int i=0;i<n;i++){
    Edge e = E[i];
    E.push_back( (Edge){ S, e.u, vs[e.u].str() } );
    E.push_back( (Edge){ e.v, T, vs[e.v].str() } );      
  }
  sort( E.begin(), E.end() );
  E.erase( unique( E.begin(), E.end() ), E.end() );
  for( Edge e : E ) {
    for(int i = 0; i < (int)G[e.u].size(); i++ ) {
      if( e.v == G[e.u][i].to ) {
        int f = remove_flow( G[e.u][i], G[e.v][G[e.u][i].rev] );
        if( f == -1 ){
          res.push_back( e.s );
          break;
        } else
          add_flow( G[e.u][i], G[e.v][ G[e.u][i].rev ] );
      }
    }
  }
  sort( res.begin(), res.end() );
  for( string s : res )
    cout << s << endl; 
}
