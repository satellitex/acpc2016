#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
double dp[2002][2002];
double calc(double p,double l,double s){return p*(l/s);}

int main(){
  int L,n,c[2001];
  double p,s[2001],S[2001]={};
  cin>>L>>p>>n;
  for(int i=0;i<L;i++)cin>>s[i],S[i+1]=s[i];
  for(int i=1;i<=L;i++)S[i]=calc(p,1,S[i])+S[i-1];
  for(int i=0;i<n;i++)cin>>c[i];
  
  for(int i=1;i<=n;i++)
    for(int j=0;j<=L;j++) dp[i][j]=INF;
  
  for(int i=0;i<n;i++)
    for(int j=0;j<=L-c[i];j++)
      dp[i+1][j+c[i]]=min(dp[i+1][j+c[i]],dp[i][j]+S[j+c[i]]-S[j]);
  
  double ans=INF;
  for(int j=0;j<=L;j++)ans=min(ans,dp[n][j]);
  printf("%.8f\n",ans);
  
  return 0;
}
