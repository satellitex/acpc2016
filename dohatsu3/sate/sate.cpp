#include<bits/stdc++.h>
using namespace std;

string S;
int N;
int nums[256];

struct Seg {
  vector<int> d;
  int n;  
  void init(int _n){
    n = 1;
    while( n < _n  ) n *= 2;
    d.resize( 2 * n );
  }
  void add(int a, int b, int x,int k, int l, int r ){
    if( a >= r || l >= b ) return;
    else if( a <= l && r <= b ) d[k] += x;
    else {
      add( a, b, x, 2*k+1, l, (l+r)/2 );
      add( a, b, x, 2*k+2, (l+r)/2, r );
    }
  }

  int get(int id){
    id += n-1;
    int ret = d[id];
    while( id ){
      id = (id-1)/2;
      ret += d[id];
    }
    return ret;
  }
  
  void add(int a,int b,int x){
    add( a, b, x, 0, 0, n );
  }
};

bool check(){
  for(int c : S)
    nums[c]++;
  for(int i='a';i<='z';i++) if( nums[i] & 1 ) return false;
  return true;
}

Seg seg;
bool used[100005];
int main(){
  cin >> S; N = S.size();
  if( check() ) {
    stack<int> st[256];
    bool rv[256]={};
    vector<int> v(N);
    for(int i=0;i<N;i++){
      int c = S[i];
      if( (int)st[c].size() >= nums[c]/2 ) rv[c] = true;
      if( rv[c] ){
        int id = st[c].top(); st[c].pop();
        v[id] = N-i-1;
        v[i] = N-id-1;
      } else 
        st[c].push( i );
    }
    seg.init( N );
    for( int t : v ) seg.add( t, N, 1 );
    long long res = 0;
    int m = v.size();
    for(int i=0;i<m;i++){
      if( used[i] ) continue;
      seg.add( v[i], N, -1 );
      res += (long long)seg.get( v[i] );
      seg.add( v[ N-v[i]-1 ], N, -1 );
      used[i] = used[ N-v[i]-1 ]  = true;
    }   
    cout << res << endl;
  } else
    cout << -1 << endl;
}
