#include<bits/stdc++.h>
using namespace std;
int n,m,k;
pair<int,int> a[15];
int dfs(int p,int s,int d,int g){
  int t=0;
  if(d==k)return s+g;
  for(int i=p;i>=0;i--)
    t=max(t,dfs(i+1,s+a[i].first*min(g,a[i].second),d+1,max(g-a[i].second,0)));
  return t;
}
int main(){
  cin>>n>>m>>k;
  for(int i=0;i<n;i++)cin>>a[i].first;
  for(int i=0;i<n;i++)cin>>a[i].second;
  sort(a,a+n);
  cout<<dfs(n-1,0,0,m)<<endl;
  return 0;
}
