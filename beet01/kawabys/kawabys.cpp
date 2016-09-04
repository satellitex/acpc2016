#include<bits/stdc++.h>
using namespace std;
int main(){
  double n,k,c,an,b;
  cin>>n>>k;
  k=min(k,n-k);
  c=M_PI*2/n;
  b=sin(c/2);
  an=(cos(c/2)*-tan(M_PI*(k-1)/n)*b)*b*n;
  printf("%.8f¥n",an);
  return 0;
}
