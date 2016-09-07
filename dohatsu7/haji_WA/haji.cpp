#include <bits/stdc++.h>
#define N 5000
#define INF 1e9
#define f first
#define s second
using namespace std;
typedef pair<int,int> P;
vector <P> G[N];
int n,m;

int dijkstra(){
  int D[N];
  for(int i=0;i<n;i++) D[i]=INF;
  priority_queue<P,vector<P>,greater<P> >Q;
  Q.push(P(1,0));
  D[0]=1;
 
  while(!Q.empty()){
    P t=Q.top();Q.pop();
    int cost=t.f,pos=t.s;
    if(D[pos]<cost)continue;
    for(int i=0;i<G[pos].size();i++){
      int ncost=G[pos][i].f,npos=G[pos][i].s;
      if(ncost>=cost)Q.push(P(ncost,npos)),D[npos]=min(D[npos],ncost);
    }
  }
  
  int res=-1;
  for(int i=0;i<n;i++)
    for(int j=0;j<G[i].size();j++)
      if(G[i][j].s==n-1&&D[i]!=INF)res=max(res,G[i][j].f);
  
  return res;
}

int main(){
  cin>>n>>m;
  for(int i=0,a,b,c;i<m;i++){
    cin>>a>>b>>c;
    G[a-1].push_back(P(c,b-1));
  }
  cout <<dijkstra()<<endl; 
  return 0;
}
