#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> P;
int N,M,K;
int A[30],B[30];


int get( vector<P> &v ){
  int k = M;
  int res = 0;
  for(P p : v ){
    if( k > p.second ){
      res += p.first * p.second;
      k -= p.second;
    }    
    else {
      res += p.first * k;
      k = 0;
    }
  }
  return res + k;
}

int main(){
  cin >> N >> M >> K;
  for(int i=0;i<N;i++)
    cin >> A[i];
  for(int i=0;i<N;i++)
    cin >> B[i];
  
  int res = 0;
  for(int i=0;i<(1<<N);i++){
    if( __builtin_popcount( i ) != K ) continue;
    vector<P> v;
    for(int j=0;j<N;j++){
      if( i & (1<<j) ) {
        v.push_back( P( A[j], B[j] ) );
      }
    }
    sort( v.rbegin(), v.rend() );
    res = max( res, get( v ) );
  }
  cout << res << endl;
}
