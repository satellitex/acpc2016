#include<bits/stdc++.h>
using namespace std;
int main(){
  int x,y,z,p,a,b,c,i,j,k,ans=0;
  cin >> x >> y >> z >> p;
  int m[x][y];
  memset(m,0,sizeof(m));
  for(i=0;i<p;i++){
    cin >> a >> b >> c;
    m[a][b]++;
  }
  for(i=0;i<y;i++){
    for(j=0;j<x;j++){
      cin >> k;
      ans+=k*m[j][i];
    }
  }
  cout << ans << endl;
  return 0;
}
