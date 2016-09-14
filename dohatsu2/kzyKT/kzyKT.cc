#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef pair<int,int> P;
int main() {
  int n,m,x,y,f=0;
  cin >> n >> m;
  vector<P> v;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    for(int j=0; j<m; j++) {
      if(s[j]=='@') x=i,y=j;
      if(s[j]=='o') v.push_back(P(i,j));
    }
  }
  if(m==1||n==1) {
    if(m==1) {
      swap(x,y);
      for(int i=0; i<v.size(); i++) swap(v[i].F,v[i].S);
    }
    v.push_back(P(0,max(n,m)));
    for(int i=0; i<v.size(); i++)if(v[i].S-i<=y&&y<=v[i].S) f=1;
    v[v.size()-1]=P(0,-1);
    sort(v.begin(),v.end());
    for(int i=0; i<v.size(); i++)if(v[i].S<=y&&y<=v[i].S+v.size()-i-1) f=1;
  } else {
    if(v.size()==1&&((!x||x==n-1||x==v[0].F)&&(!y||y==m-1)||(!x||x==n-1)&&y==v[0].S)) f=1;
    if(v.size()==2) {
      if(!x||!y||x==n-1||y==m-1) f=1;
      if(v[0].F==v[1].F)if(y==1||y==v[0].S+1||y==v[1].S-1||y==m-2) f=1;
      if(v[0].S==v[1].S)if(x==1||x==v[0].F+1||x==v[1].F-1||x==n-2) f=1;
    }
    if(v.size()>=3) f=1;
  }
  cout << (f?"yes":"no") << endl;
  return 0;
}
