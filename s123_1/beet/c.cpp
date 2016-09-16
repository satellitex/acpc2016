#include<bits/stdc++.h>
using namespace std;
struct E{int to,cost;E(int to,int cost):to(to),cost(cost){}};
typedef pair<int,int> P;
typedef pair<int,P> PP;
#define F first
#define S second
int main(){
  int n,m,r,i,j,k,a,b,c;
  cin>>n>>m>>r;
  int d[n];
  vector<E> v[n];
  for(i=0;i<n;i++) cin>>d[i];
  for(i=0;i<m;i++){
    cin >> a >> b >> c;
    a--;b--;
    v[a].push_back(E(b,c));
    v[b].push_back(E(a,c));
  }
  for(i=0;i<n;i++) v[i].push_back(E(i,15));
  int dp[1050][50]={};
  dp[0][0]=-1;
  priority_queue<PP> q;
  q.push(PP(0,P(0,0)));
  while(!q.empty()){
    PP pp=q.top();q.pop();
    c=pp.F;a=pp.S.F;b=pp.S.S;
    if(a==n-1) cout << c << ":" << a << ":" << b << endl;
    if(dp[c][a]>=b) continue;
    dp[c][a]=b;
    for(i=0;i<v[a].size();i++){
      if(c+v[a][i].cost<=r)
	q.push(PP(c+v[a][i].cost,P(v[a][i].to,b+d[v[a][i].to])));
    }
  }
  int ans=0;
  for(i=0;i<=r;i++) ans=max(ans,dp[i][n-1]);
  cout << ans << endl;
  return 0;
}
