#include <bits/stdc++.h>
using namespace std;

int main() {
  long long n,d,x,sum;
  cin >> n >> d;
  x=n-d+1;
  if(d==2) x++;
  sum=x*(x-1)/2+d-1;
  if(d==2) sum-=2;
  cout << sum << endl;
  return 0;
}
