#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
double PI = acos(-1);
double N,K;

double total=0;

double change(double x){
  return x/(2.0*PI)*360.0;
}

int main(){
  cin>>N>>K;
  double ti = PI * 2.0 / N;
  double u =  ( PI - 2.0 * PI * K / N ) * 0.5;
  
  double TI = ( PI - ti ) * 0.5 - u;

  TI = PI - TI - TI;
  
  total = 1.0 * 1.0 * sin(ti) * 0.5 * N;

  
  double ww=1.0+1.0-2.0*cos( ti );
  
  double kk=ww/(1.0-cos(TI))/2.0;
  
  printf("%.10f\n", total - (kk*sin(TI)*0.5)*N );  
  return 0;
}
