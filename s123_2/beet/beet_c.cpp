#include<bits/stdc++.h>
using namespace std;
int n,m,k,ans=0;
int a[20],b[20];
int memo[10050][20][4];
int rec(int x,int y,int z){//x=imo;y=men;z=mensuu
  int res=0,i,j;
  if(~memo[x][y][z]) return memo[x][y][z];
  if(z==k) return memo[x][y][z]=m-x;
  if(x==m) cout << x << ":" << y << ":" << z << endl;
  for(i=y;i<n;i++){
    for(j=1;x+j<=m;j++){
      if(j>b[i]) break;
      res=max(res,a[i]*j+rec(x+j,i+1,z+1));
    }
  }
  return memo[x][y][z]=res;
}
int main(){
  int i,j;
  cin>>n>>m>>k;
  for(i=0;i<n;i++) cin>>a[i];
  for(i=0;i<n;i++) cin>>b[i];
  memset(memo,-1,sizeof(memo));
  cout << rec(0,0,0) << endl;
  return 0;
}
