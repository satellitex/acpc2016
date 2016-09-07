#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct BIT {
  vector<int> data;
  int sz;
  BIT(int n)
  {
    sz = n;
    data.resize(sz + 1, 0);
  }
  void add(int k, int x)
  {
    while(k <= sz) {
      data[k] += x;
      k += k & -k;
    }
  }
  int sum(int k)
  {
    int s = 0;
    while(k > 0) {
      s += data[k];
      k -= k & -k;
    }
    return s;
  }
  int rsum(int i, int j)
  {
    return sum(j) - sum(i);
  }
};

int main()
{
  string s;
  cin >> s;
  
  BIT bit(s.size());  
  stack<int> stk[26];  
  for(int i = 0; i < s.size(); i++) {
    stk[s[i]-'a'].push(i);
    bit.add(i+1, 1);
  }

  for(int i = 0; i < 26; i++) {
    if(stk[i].size() % 2) {
      cout << -1 << endl;
      return 0;
    }
  }

  ll ans = 0;
  bool used[400002] = {false};
  for(int i = 0; i < s.size(); i++) {
    if(used[i]) continue;
    int idx = stk[s[i]-'a'].top(); stk[s[i]-'a'].pop();
    used[idx] = true;
    ans += bit.rsum(idx+1, s.size());
    bit.add(idx+1, -1);
  }

  cout << ans << endl;
  
  return 0;
}
