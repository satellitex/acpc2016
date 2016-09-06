#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N, M, K;
ll a[20], b[20];

int main()
{
  cin >> N >> M >> K;
  
  a[0] = b[0] = 0; N++;
  for(int i = 1; i < N; i++) cin >> a[i];
  for(int i = 1; i < N; i++) cin >> b[i];

  ll ans = M;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < N; k++) {
	if(i && j && i == j ||
	   j && k && j == k ||
	   k && i && k == i) continue;	
	if((a[i]>0) + (a[j]>0) + (a[k]>0) > K) continue;
	int idx[] = {i, j, k};
	ll m = M, pro = 0;
	for(int l = 0; l < 3; l++) {
	  int dep = min(m, b[idx[l]]);
	  pro += dep*a[idx[l]];
	  m -= dep;
	}
	ans = max(ans, m + pro);
      }
    }
  }

  cout << ans << endl;

  return 0;
}
