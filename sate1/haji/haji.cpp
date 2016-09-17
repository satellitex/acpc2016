#include <bits/stdc++.h>
#define N 100000
using namespace std;
struct po{int dep,cnt;};
vector <int> G[N];
int n,D[N],mxd,mxn;

void dfs(int pos,int pre,int dep){
  if(mxd<=dep) mxd=dep,mxn=pos;
  D[pos]=max(D[pos],dep);
  for(int i=0;i<G[pos].size();i++)
    if(G[pos][i]!=pre) dfs(G[pos][i],pos,dep+1);
}

po dfs2(int pos,int pre){
  po res=po{0,0};
  for(int i=0;i<G[pos].size();i++)
    if(G[pos][i]!=pre){
      po a=dfs2(G[pos][i],pos);
      res.cnt+=a.dep+a.cnt;
      res.dep=max(res.dep,a.dep);
    }
  return po{res.dep+1,res.cnt+1-res.dep};
}

int main(){
  cin>>n;
  for(int i=0,a,b;i<n-1;i++){
    scanf("%d%d",&a,&b);
    G[a-1].push_back(b-1);
    G[b-1].push_back(a-1);
  }

  dfs(0,-1,0),dfs(mxn,-1,0),dfs(mxn,-1,0);
  po res=dfs2(mxn,-1);
  for(int i=0;i<n;i++)printf("%d\n",res.cnt+(mxd-D[i]-1));
  return 0;
}
