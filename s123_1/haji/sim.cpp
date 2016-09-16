#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
typedef pair<int,int> P;
vector <int> path;
int ball[31];
int G[31][31];

int main(){
   int n,m,r;
  cin>>n>>m>>r;
  for(int i=0;i<n;i++) cin>>ball[i];
  
  for(int i=0;i<n;i++) 
    for(int j=0;j<n;j++)G[i][j]=INF;

  for(int i=0,a,b,c;i<m;i++){
    cin>>a>>b>>c;
    G[a-1][b-1]=G[b-1][a-1]=c;
  }
  
  for(int k=0;k<n;k++)
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
	G[i][j]=min(G[i][j],G[i][k]+G[k][j]);	
  for(int i=0;i<n;i++)G[i][i]=15;
  

  int p;
  cin>>p;
  path.resize(p);
  for(int i=0,a;i<p;i++)cin>>path[i]; 
  int cnt=0,t=0;
  int used[30];
  for(int i=0;i<30;i++) used[i]=-300;

  for(int i=1;i<p;i++){
    int pos=path[i];

    int cost=G[path[i-1]][pos];

    if(t+cost-used[pos]>=15){
      cnt+=ball[pos];
      t+=cost;
    }else{
      t=used[pos]+15;
      cnt+=ball[pos];
    }
    used[pos]=t;
  }
  cout <<cnt<<" "<<t<<endl;

  

  return 0;
}
