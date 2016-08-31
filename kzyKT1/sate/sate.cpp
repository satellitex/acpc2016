#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,D;

ll sum( ll n ){
  return n * ( n + 1 ) / 2;
}

int main(){
  cin >> N >> D;
  ll K = N - D + 1;
  ll sm = sum( K - 1 );
  if( D == 1 ) cout << sm << endl;
  else 
    cout << sm + D-1 + ( K > 2 ? K - 2 : 0 ) << endl;
}
