#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
  ll n,d,ans=0;
  cin>>n>>d;
  ans=(n-d-1)*(n-d-2)/2+d+min(d+1,3LL)*(n-d-1);
  cout << ans << endl;
  return 0;
}
