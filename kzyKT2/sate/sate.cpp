#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
int N,M,K;
vector<P> ps;

const int INF = INT_MAX;
struct segtree{
  //最小値を求める用
  vector<int> datamin;
  //遅延用
  vector<int> delay;
  int n;
  //初期化
  void init(int _n){
    n = 1;
    while( n < _n ) n*=2;
    datamin.resize( 2 * n, 0 );
    delay.resize( 2 * n, 0 );
  }

  //クリア(何度も使う場合）
  void clear(){
    datamin.clear();
    delay.clear();
  }
 
  //簡易版（総和に対する処理無しand0初期化無しver)
  void delaycalc(int k){
    datamin[k] = datamin[k]+delay[k];
    if( k+1 < n )
      for(int i=1;i<=2;i++)
	delay[2*k+i] = delay[2*k+i]+delay[k];
    delay[k] = 0;
  }
  

  //区間　[a,b)　に一様に　x　を足す 
  void add(int a,int b,int x,int k,int l,int r){
    delaycalc(k);
    if( r<=a || b<=l ) return;
    else if( a<=l && r<=b ){
      delay[k] = x;
      delaycalc(k);
    } else {
      add( a, b, x, 2*k + 1, l, (l+r)/2 );
      add( a, b, x, 2*k + 2, (l+r)/2, r );
      datamin[k] = min( datamin[2*k+1], datamin[2*k+2] );
    }
  }
  //ある区間の最小値を求める
  int querymin(int a,int b,int k,int l,int r){
    delaycalc(k);
    if( r<=a || b<=l ) return INF;
    if( a<=l && r<=b ){
      return datamin[k]+delay[k];
    } else {
      int vl = querymin( a, b, 2*k+1, l,(l+r)/2 );
      int vr = querymin( a, b, 2*k+2, (l+r)/2,r );
      return min(vl,vr);
    }
  }

  //各簡易クエリ呼び出し
  void add( int a,int b,int x){ add( a, b, x, 0,0,n); }//加える
  int querymin(int a,int b){ return querymin(a,b,0,0,n); }//最小値取得
};


segtree S[2];
void init(int size){
  S[0].clear();
  S[0].init(size);
  for(int i=0;i<size;i+=2)
    S[0].add( i, i+1, 1 );    
  S[1].clear();
  S[1].init(size);
  for(int i=1;i<size;i+=2)
    S[1].add( i, i+1, 1 );
}
void add(int a,int b,int x){
  S[0].add( a, b, x );
  S[1].add( a, b, x );
}
int querymin(int a,int b,int now){
  return S[now].querymin( a, b );
}


P change(P p){  
  int nx = p.first - p.second + M;
  int ny = p.first + p.second + 1;
  return P( nx, ny );
}

struct state {
  int l,r,c;
  state(){}
  state(int l,int r,int c):l(l),r(r),c(c){}
};

const int MAX_Q = 222222;
vector<state> query[MAX_Q];

void calcQuery(int h){
  for(int i=0;i<MAX_Q;i++) query[i].clear();  
  for( P p : ps ){
    P t = change( p );
    int u = max( 1, t.second - h );
    int d = min( MAX_Q-1, t.second+h+1 );
    int l = max( 0, t.first - h ), r = min( N+M+1, t.first + h + 1 );    
    query[ u ].push_back( state( l, r, 1 ) );
    query[ d ].push_back( state( l, r, -1 ) );
  }
}

bool check(int h){
  int size = N + M + 1;
  calcQuery( h );
  init( size );
  int l = change(P(0,0)).first;
  int r = l+1;  
  int now = 1;
  if( l&1 ) now = 0;
  for(int i=1;i<N+M;i++){
    for( state q : query[i] ){
      add( q.l, q.r, q.c );
    }
    int x = querymin( l, r, now );
    if( x == 0 ) return false;
    if( i < M ) l--; 
    else l++;
    if( i < N ) r++;
    else r--;
    now = 1-now;
  }
  return true;
}

int main(){
  cin >> N >> M >> K;
  ps.resize(K);
  for( P &p : ps ) cin >> p.first >> p.second;

  int res;
  int l=0, r=N+M;
  while( l <= r ){
    int h = (l+r)/2;
    if( check(h) ){
      r = h-1;
      res = h;
    } else
      l = h+1;
  }
  cout << res << endl;  
}
