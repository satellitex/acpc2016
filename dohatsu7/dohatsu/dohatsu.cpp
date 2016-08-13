#include<bits/stdc++.h>
using namespace std;
#define MAX_N 5001
struct edge{ int to,cost; };
typedef pair<int,int> P;

int N,M;
int d[MAX_N];
vector< edge > G[MAX_N];

int main(){
  cin>>N>>M;
  for(int i=0;i<M;i++){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    G[a].push_back((edge){b,c});
  }
  
  int ans=0;  
  priority_queue< P , vector<P> , greater<P> > Q;

  fill(d,d+MAX_N,1e9);
  Q.push(P(1,1));
  d[1]=1;
  while(!Q.empty()){
    P p=Q.top();Q.pop();
    int pos=p.second;
    int cost=p.second;
    if(d[pos]<cost)continue;
    for(int i=0;i<(int)G[pos].size();i++){
      edge e=G[pos][i];
      if(e.cost<d[pos])continue;
      if(e.to==N)ans=max(ans,e.to);
      if(d[e.to]>e.cost){
        d[e.to]=e.cost;
        Q.push(P(d[e.to],e.to));
      }
    }
  }

  printf("%d\n",ans);
  return 0;
}
