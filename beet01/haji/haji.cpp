#include <bits/stdc++.h>
using namespace std;
int N,K;

double Rad(double a){return a*M_PI/180;}

double solve(){
  double center=(360.0)*(N-2*K)/N;
  double center2=360.0/N;
  double d=sin(Rad(center2/2))*2;
  double kaku=((180-center/2)/2-center2/2);
  double s=d*(d/2*tan(Rad(kaku)))/2;
  double S=cos(Rad(center2/2))*d*N/2;
  return S-s*N;
}

int main(){
  cin>>N>>K;
  K=min(K,N-K);
  printf("%.8f\n",solve());
  return 0;
}
