#include<bits/stdc++.h>
using namespace std;
struct happy{
  int d,a,k,t;
  bool operator<(const happy h) const{
    if(d!=h.d) return d<h.d;
    return a<h.a;
  }
};
int main(){
  int n,m,l,i,j,k,a,b,ans=0;
  cin>>n>>m>>l;
  vector<happy> v;
  happy h;
  for(i=0;i<m;i++){
    cin>>h.d>>h.a>>h.k>>h.t;
    v.push_back(h);
  }
  sort(v.begin(),v.end());
  int dp[5][10][50]={};
  for(i=0;i<m;i++){
    for(j=0;j<=v[i].d;j++){
      for(k=0;k<=n+1;k++){
	if(j==v[i].d&&k>v[i].a) break;
	for(a=0;a<l;a++){
	  dp[v[i].d][v[i].a+v[i].k][a+1]
	    =max(dp[v[i].d][v[i].a+v[i].k][a+1],
		 dp[j][k][a]+v[i].t);
	  ans=max(ans,dp[v[i].d][v[i].a+v[i].k][a+1]);
	}
      }
    }
  }
  cout << ans << endl;
  return 0;
}
