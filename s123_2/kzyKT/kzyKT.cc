#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

int main() {
  int n,m,k;
  cin >> n >> m >> k;
  P a[n];
  for(int i=0; i<n; i++) cin >> a[i].first;
  for(int i=0; i<n; i++) cin >> a[i].second;
  sort(a,a+n,greater<P>());
  int ans=0;
  for(int t=0; t<(1<<n); t++) {
    if(__builtin_popcount(t)>k) continue;
    int sum=0,x=m;
    for(int i=0; i<n; i++) {
      if(!(t&(1<<i))) continue;
      sum+=min(x,a[i].second)*a[i].first;
      x-=min(x,a[i].second);
    }
    ans=max(ans,sum+x);
  }
  cout << ans << endl;
  return 0;
}
