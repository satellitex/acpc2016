#include<bits/stdc++.h>
using namespace std;

int n,m,r,a,b,c;

int G[50][50];
int x[50];
int dp[50][50][1001];

int main(){

  fill( (int*)G[0] , (int*)G[50] , 1e9);
  fill( (int*)dp[0] , (int*)dp[50] , -1e9);
  
  for(int i=0;i<50;i++)G[i][i]=0;

  cin>>n>>m>>r;
  for(int i=0;i<n;i++)cin>>x[i];  
  for(int i=0;i<m;i++){
    cin>>a>>b>>c;
    a--,b--;
    G[a][b]=min(G[a][b],c);
    G[b][a]=min(G[b][a],c);
  }

  
  for(int k=0;k<n;k++)
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        G[i][j]=min(G[i][j],G[i][k]+G[k][j]);

  int ans=0;
  
  dp[0][0][0]=0;
  for(int t=0;t<=r;t++){
    for(int pos=0;pos<n;pos++){
      for(int prev=0;prev<n;prev++){
        if(dp[pos][prev][t]==-1e9)continue;
        int cnt=dp[pos][prev][t];
        
        if(pos==n-1)ans=max(ans,cnt);
        
        for(int to=0;to<n;to++){
          int cost=G[pos][to];
          
          if(to==prev){
            
            cost=max(cost,15-G[pos][to]);
            if(t+cost<=r)
              dp[ prev ][ prev ][ t+cost ]=
                max( dp[ prev ][ prev ][ t+cost ] , cnt + x[prev] );
            
          }else{
            if(to==pos)cost=15;
            if(t+cost<=r)
              dp[ to ][ pos ][ t+cost ] =
                max( dp[ to ][ pos ][ t+cost ] , cnt + x[to] );
          }
        
        }// to
      }// pos
    }// prev
  }// t
  cout<<ans<<endl;
  return 0;
}
