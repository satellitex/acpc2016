#include<bits/stdc++.h>
using namespace std;
int dp[2050][50][50]={};
struct E{int to,cost;E(int to,int cost):to(to),cost(cost){}};
struct status{
  int cur,pre,time,num;
  bool f;
  status(int time,int cur,int pre,int num):
    cur(cur),pre(pre),time(time),num(num){}
  bool operator<(const status  s) const{
    return time>s.time;
  }
};
int main(){
  int n,m,r,i,j,k,a,b,c;
  cin>>n>>m>>r;
  int d[n];

  int e[n][n];
  memset(e,-1,sizeof(e));
  vector<E> v[n];
  for(i=0;i<n;i++) cin>>d[i];
  for(i=0;i<m;i++){
    cin >> a >> b >> c;
    a--;b--;
    v[a].push_back(E(b,c));
    v[b].push_back(E(a,c));

    e[a][b]=c;
    e[b][a]=c;
  }

  
  int ed[n][n];
  memset(ed,-1,sizeof(ed));
  vector<E> st[n];
  
  bool used[n];
  int di[n];
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(i==j) continue;
      memset(used,0,sizeof(used));
      memset(di,-1,sizeof(di));
      di[i]=0;
      while(1){
	int v=-1;
	for(k=0;k<n;k++){
	  if(!used[k]&&~di[k]&&(v==-1||di[k]<di[v])) v=k;
	}
	if(!~v) break;
	used[v]=true;
	for(k=0;k<n;k++){
	  if(v==i&&k==j) continue;
	  if(~e[v][k])
	    if(!~di[k]||di[v]+e[v][k]<di[k]) di[k]=di[v]+e[v][k];	  
	}
      }
      ed[i][j]=di[j];
    }
  }
  
  for(i=0;i<n;i++) ed[i][i]=15;
  
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      //cout << i << ":" << j << "/" << ed[i][j] << endl;
      if(~ed[i][j]) st[i].push_back(E(j,ed[i][j]));
    }
  }
  
  memset(dp,-1,sizeof(dp));
  priority_queue<status> q;
  q.push(status(0,0,0,0));
  while(!q.empty()){
    status s=q.top();q.pop();
    if(~dp[s.num][s.cur][s.pre]&&dp[s.num][s.cur][s.pre]<=s.time) continue;
    if(s.time>r) continue;
    cout << s.time << ":" << s.cur << ":" <<s.pre << ":" << s.num << endl;
    dp[s.num][s.cur][s.pre]=s.time;
    for(i=0;i<v[s.cur].size();i++){
      if(v[s.cur][i].to==s.pre&&v[s.cur][i].cost*2<15){
	q.push(status(s.time+v[s.cur][i].cost,v[s.cur][i].to,
		      s.cur,s.num));
	q.push(status(s.time+15-v[s.cur][i].cost,v[s.cur][i].to,
		      n,s.num+d[v[s.cur][i].to]));
      }else{
	q.push(status(s.time+v[s.cur][i].cost,v[s.cur][i].to,
		      s.cur,s.num+d[v[s.cur][i].to]));
      }
    }
    
    for(i=0;i<st[s.cur].size();i++){
      q.push(status(s.time+st[s.cur][i].cost,st[s.cur][i].to,
		    n,s.num+d[st[s.cur][i].to]));
    }
    
  }
  int ans=0;
  for(i=0;i<2050;i++)
    for(j=0;j<n;j++)
      if(~dp[i][n-1][j]&&dp[i][n-1][j]<=r)
	ans=max(ans,i);
  cout << ans << endl;
  return 0;
}
