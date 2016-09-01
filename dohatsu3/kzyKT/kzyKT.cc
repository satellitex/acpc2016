#include <bits/stdc++.h>
using namespace std;

class BIT{
public:
  int n,bit[500010];
  BIT(){fill(bit,bit+500010,0);}
  void add(int i,int x){
    while(i<=n){
      bit[i]+=x;
      i+=i&-i;
    }
  }
  int sum(int i){
    int s=0;
    while(i>0){
      s+=bit[i];
      i-=i&-i;
    }
    return s;
  }
};

int ans,c[26];
int main() {
  string s;
  cin >> s;
  BIT b=BIT();
  b.n=1<<s.size();
  vector<int> v[26];
  for(int i=0; i<s.size(); i++) v[s[i]-'a'].push_back(i);
  for(int t=0; t<s.size()/2; t++) {
    int M=1<<29,k,n=s.size();
    for(int i=0; i<26; i++) {
      if(c[i]>=v[i].size()/2) continue;
      int x=v[i][c[i]]-b.sum(v[i][c[i]]+1);
      int y=(n-1-v[i][v[i].size()-1-c[i]])-b.sum(n+1)+b.sum(v[i][v[i].size()-1-c[i]]+1);
      if(M>x+y) {
        M=x+y;
        k=i;
      }
    }
    if(M==1<<29) {
      cout << -1 << endl;
      return 0;
    }
    ans+=M;
    b.add(v[k][c[k]]+1,1);
    b.add(v[k][v[k].size()-1-c[k]]+1,1);
    c[k]++;
  }
  cout << ans << endl;
  return 0;
}
