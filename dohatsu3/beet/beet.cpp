#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
  string s;
  cin>>s;
  ll n=s.size(),h=n/2;
  priority_queue<ll,vector<ll>,greater<ll> > q[26];
  ll c[26]={},d[26]={};
  ll i,j,k,l,p=0,x=0,ans=0;
  for(i=0;i<n;i++){
    c[s[i]-'a']++;
  }
  bool f=true;
  for(i=0;i<26;i++){
    if(c[i]%2) f=false;
  }
  if(!f){
    ans=-1;
  }else{
    for(i=0;i<n;i++){
      k=s[i]-'a';
      d[k]++;
      if(d[k]<=c[k]/2){
	q[k].push(n-p-1);
	p++;
      }else{
	l=q[k].top();q[k].pop();
	ans+=l-i;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
