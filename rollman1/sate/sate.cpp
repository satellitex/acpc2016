#include<bits/stdc++.h>
using namespace std;
int L,D;
double p,S[2222];
int c[2222];
double dp[2222][2222];
double R[2222];
const double INF = 1e100;
void update(double &a, double b ){ if( a > b ) a = b; }
int main(){    
  cin >> L >> p >> D;
  for(int i=0;i<L;i++) cin >> S[i];
  for(int i=0;i<D;i++) cin >> c[i];
  for(int i=0;i<L;i++) R[i+1] = 1.0/S[i] + R[i];

  fill( dp[0], dp[L+1], INF );
  dp[0][0] = 0.0;
  for(int i=0;i<L;i++){
    for(int j=0;j<=D;j++){
      int to = i + c[j];
      update( dp[i+1][j], dp[i][j] );
      if( to > L ) continue;
      update( dp[to][j+1], dp[i][j] + p * ( R[to] - R[i] ) );
    }
  }
  printf("%.10lf\n", dp[L][D] );
}

