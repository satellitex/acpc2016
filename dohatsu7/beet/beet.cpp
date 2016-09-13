#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct E{
  ll to,cost;
  E(ll to,ll cost):to(to),cost(cost){}
};
typedef pair<ll,ll> P;
int main(){
  ll n,m,i,j,k,a,b,c;
  cin>>n>>m;
  vector<E> v[n];
  vector<E> can;
  for(i=0;i<m;i++){
    cin >> a >> b >> c;
    a--;b--;
    if(b==n-1) can.push_back(E(a,c));
    else v[a].push_back(E(b,c));
  }
  ll g[n];
  memset(g,-1,sizeof(g));
  priority_queue<P,vector<P>,greater<P> > q;
  q.push(P(1,0));
  while(!q.empty()){
    P p=q.top();q.pop();
    b=p.first;a=p.second;
    if(~g[a]&&g[a]<=b) continue;
    g[a]=b;
    for(i=0;i<v[a].size();i++){
      if(b<=v[a][i].cost)
	if(!~g[v[a][i].to]||g[v[a][i].to]>v[a][i].cost)
	  q.push(P(v[a][i].cost,v[a][i].to));
    }
  }
  ll ans=-1;
  for(i=0;i<can.size();i++)
    if(~g[can[i].to]&&g[can[i].to]<=can[i].cost) ans=max(ans,can[i].cost);
  cout << ans << endl;
  return 0;
}
