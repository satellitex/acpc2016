#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

int main() {
  int n,m,k;
  cin >> n >> m >> k;
  P a[n];
  for(int i=0; i<n; i++) cin >> a[i].first;
  for(int i=0; i<n; i++) cin >> a[i].second;
  int b[n];
  for(int i=0; i<n; i++) b[i]=i<k?1:0;
  sort(b,b+n);
  int ans=0;
  do {
    vector<P> v;
    for(int i=0; i<n; i++) {
      if(b[i]) v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    do {
      int sum=0,x=m;
      for(int i=0; i<v.size(); i++) {
        sum+=min(x,v[i].second)*v[i].first;
        x-=min(x,v[i].second);
      }
      ans=max(ans,sum+x);
    } while(next_permutation(v.begin(),v.end()));
  } while(next_permutation(b,b+n));
  cout << ans << endl;
  return 0;
}
