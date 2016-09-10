#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
  ll n,d;
  cin>>n>>d;
  if(d==1) cout <<n*(n-1)/2<<endl;
  else {
    ll ans=d-2;
    ll a=3+(n-(d+1));
    ans+=a*(a-1)/2-1;
    cout<<ans<<endl;
  }
  
  return 0;
}
