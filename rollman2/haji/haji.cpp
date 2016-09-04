#include <bits/stdc++.h>
using namespace std;
int mp[60][60];

int main(){
  int X,Y,Z,p;
  cin>>X>>Y>>Z;
  cin>>p;
  for(int i=0,x,y,z;i<p;i++){
    cin>>x>>y>>z;mp[x][y]++;
  }
  
  int ans=0;
  for(int i=0;i<Y;i++)
    for(int j=0,a;j<X;j++){
      cin>>a;
      ans+=mp[i][j]*a;
    }
  cout <<ans<<endl;

  return 0;
}
