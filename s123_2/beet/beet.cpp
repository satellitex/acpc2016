#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans=0;
typedef pair<int,int> P;
vector<P> v;
int rec(int x,int y,int z){//x=imo;y=men;z=mensuu
  int res=0,i,j;
  if(z==k) return m-x;
  for(i=y;i<n;i++){
    j=min(v[i].second,m-x);
    res=max(res,v[i].first*j+rec(x+j,i+1,z+1));
  }
  return res;
}
int main(){
  int i,j;
  cin>>n>>m>>k;
  v.resize(n);
  for(i=0;i<n;i++) cin>>v[i].first;
  for(i=0;i<n;i++) cin>>v[i].second;
  sort(v.begin(),v.end(),greater<P>());
  cout << rec(0,0,0) << endl;
  return 0;
}
