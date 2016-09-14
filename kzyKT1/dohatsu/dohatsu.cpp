#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N,M;

ll calc(ll x){
  x--;
  return (1+x)*x/2;
}


ll solve(){
  if(M==1)return N*(N-1)/2;
  if(M==2)return N*(N-1)/2-1;
  
  ll n=N-M+1;
  ll ans=n*(n-1)/2+M-1;
  ans+=n-2;
  return ans;
}
int main(){
  cin>>N>>M;
 
  cout<<solve()<<endl;


  
  return 0;
}
