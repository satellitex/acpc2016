#include<bits/stdc++.h>
using namespace std;

int X,Y,Z;
int p;
int F[55][55];
int main(){
  cin >> X >> Y >> Z;
  cin >> p;
  for(int i=0;i<p;i++){
    int a,b,c; cin >> a >> b>> c;
    F[a][b]++;
  }
  int res = 0;
  for(int y=0;y<Y;y++){
    for(int x=0;x<X;x++){
      int f; cin >> f;
      if( f )  res += F[x][y];
    }
  }
  cout << res << endl;
}
