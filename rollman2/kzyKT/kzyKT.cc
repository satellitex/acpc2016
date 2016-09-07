#include <bits/stdc++.h>
using namespace std;

int d[55][55],n,m,k,q,ans;
int main() {
  cin >> n >> m >> k >> q;
  for(int i=0,x,y,z;i<q;i++) {
    cin >> x >> y >> z;
    d[y][x]++;
  }
  for(int i=0;i<m;i++) {
    for(int j=0,x;j<n;j++){
      cin >> x;
      ans+=d[i][j]*x;
    }
  }
  cout << ans << endl;
  return 0;
}
