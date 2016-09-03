#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef pair<int,int> P;
P a[20];

int calc(vector<P> a,int m){
  int res=0;
  for(int i=0;i<a.size()&&m>0;i++){
    res+=a[i].f*min(a[i].s,m);
    m-=a[i].s;
  }
  if(m>0)res+=m;
  return res;
}

int main(){
  int n,m,K;
  cin>>n>>m>>K;
  for(int i=0;i<n;i++) cin>>a[i].f;
  for(int i=0;i<n;i++) cin>>a[i].s;
  sort(a,a+n,greater<P>());

  int ans=m;
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n+1;j++)
      for(int k=j+1;k<n+2;k++){
	vector<P> b;
	b.push_back(a[i]);
	if(K>=2)b.push_back(a[j]);
	if(K>=3)b.push_back(a[k]);
	ans=max(ans,calc(b,m));
      }
  cout <<ans<<endl;
  return 0;
}
