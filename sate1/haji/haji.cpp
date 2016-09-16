#include <bits/stdc++.h>
#define N 100000
#define f first
#define s second
using namespace std;
typedef pair<int,int> P;
typedef pair<P,int> PP;
vector <int> G[N];
vector <PP> D[N];
int dis[N];
int n,L;
int start,goal;

void dfs(int pos,int pre,int dep,int &a){
  if(L<dep) L=dep,a=pre;
  dis[pos]=dep;
  for(int i=0;i<G[pos].size();i++)
    if(G[pos][i]!=pre) dfs(G[pos][i],pos,dep+1,a);
}

P mem[N];
P dfs2(int pos,int pre,int dep){
  if(mem[N].f!=-1) return mem[N];
  int cnt=1,ndep=0;
  P res;
  for(int i=0;i<G[pos].size();i++){
    if(G[pos][i]==pre)continue;
    res=dfs2(G[pos][i],pos,dep+1);
    cnt+=res.f+res.s;
    ndep=max(ndep,res.f);
  }
  return mem[pos]=P(ndep,cnt);
}

P bfs(){
  

}

int main(){
  cin>>n;
  for(int i=0,a,b;i<n-1;i++){
    cin>>a>>b;a--,b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  dfs(0,-1,0,start);
  memset(dis,0,sizeof(dis));
  dfs(start,-1,0,goal);
  memset(mem,-1,sizeof(mem));
  
  for(int i=0;i<n;i++)cout <<dfs2(i,-1,0).s<<endl;
  return 0;
}
