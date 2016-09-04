#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[15],b[15];
int dfs(int p,int s,int d,int g){
  int t=0;
  if(d==k)return s+g;
  for(int i=p;i<n;i++)
    t=max(t,dfs(i+1,s+a[i]*min(g,b[i]),d+1,max(g-b[i],0)));
  return t;
}
int main(){
  cin>>n>>m>>k;
  for(int i=0;i<n;i++)cin>>a[i];
  for(int i=0;i<n;i++)cin>>b[i];
  cout<<dfs(0,0,0,m)<<endl;
  return 0;
}
