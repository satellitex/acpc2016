#include<bits/stdc++.h>
using namespace std;
int dp[2050][50][50][2]={};
int dp2[1050][50][50][2]={};
struct E{int to,cost;E(int to,int cost):to(to),cost(cost){}};
struct status{
  int cur,pre,time,num;
  bool f,pf;
  status(int time,int cur,int pre,int num,bool f,bool pf):
    cur(cur),pre(pre),time(time),num(num),f(f),pf(pf){}
  bool operator<(const status &s) const{
    return time>s.time;
  }
};
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
  memset(dp,-1,sizeof(dp));
  memset(dp2,-1,sizeof(dp2));
  priority_queue<status> q;
  q.push(status(0,0,0,0,0,0));
  while(!q.empty()){
    status s=q.top();q.pop();
    if(s.time>r) continue;
    if(~dp[s.num][s.cur][s.pre][s.pf]&&
       dp[s.num][s.cur][s.pre][s.pf]<=s.time) continue;
    dp[s.num][s.cur][s.pre][s.pf]=s.time;
    if(~dp2[s.time][s.cur][s.pre][s.pf]&&
       dp2[s.time][s.cur][s.pre][s.pf]>=s.num) continue;
    dp2[s.time][s.cur][s.pre][s.pf]=s.num;
    
    //cout <<s.time<<":"<<s.cur<<":"<<s.pre<<":"<<s.num<<":"<<s.pf<<endl;
    for(i=0;i<v[s.cur].size();i++){
      if(s.time+v[s.cur][i].cost > r) continue;
      if(v[s.cur][i].to==s.pre&&v[s.cur][i].cost*2<15&&s.pf){
	if(!~dp[s.num][v[s.cur][i].to][s.cur][s.f]||
	   dp[s.num][v[s.cur][i].to][s.cur][s.f]>s.time+v[s.cur][i].cost)
	  q.push(status(s.time+v[s.cur][i].cost,v[s.cur][i].to,
			s.cur,s.num,false,s.f));
	if(!~dp[s.num+d[v[s.cur][i].to]][v[s.cur][i].to][s.cur][s.f]||
	   dp[s.num+d[v[s.cur][i].to]][v[s.cur][i].to][s.cur][s.f]>s.time+15-v[s.cur][i].cost)
	  q.push(status(s.time+15-v[s.cur][i].cost,v[s.cur][i].to,
			n,s.num+d[v[s.cur][i].to],true,s.f));
      }else{
	if(!~dp[s.num+d[v[s.cur][i].to]][v[s.cur][i].to][s.cur][s.f]||
	   dp[s.num+d[v[s.cur][i].to]][v[s.cur][i].to][s.cur][s.f]>s.time+v[s.cur][i].cost)
	  q.push(status(s.time+v[s.cur][i].cost,v[s.cur][i].to,
			s.cur,s.num+d[v[s.cur][i].to],true,s.f));
      }
      
    }
  }

  int ans=0;
  for(i=0;i<2050;i++)
    for(j=0;j<n;j++)
      for(k=0;k<2;k++)
	  if(~dp[i][n-1][j][k]&&dp[i][n-1][j][k]<=r)
	    ans=max(ans,i);
  
  cout << ans << endl;
  return 0;
}
