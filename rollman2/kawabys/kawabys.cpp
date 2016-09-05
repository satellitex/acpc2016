#include<bits/stdc++.h>
using namespace std;
int c[51][51],m,n,o,p,x,y,z,an;
int main(){
  cin>>m>>n>>o>>p;
  for(int i=0;i<p;i++)cin>>x>>y>>z,c[x][y]++;
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)cin>>x,an+=c[j][i]*x;
  cout<<an<<endl;
  return 0;
}
