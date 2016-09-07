#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

int main() {
  int n,m;
  cin >> n >> m;
  vector<P> v[n],g;
  for(int i=0; i<m; i++) {
    int x,y,z;
    cin >> x >> y >> z;
    x--,y--;
    v[x].push_back(P(y,z));
    if(y==n-1) g.push_back(P(x,z));
  }
  int d[n];
  fill(d,d+n,1<<29);
  d[0]=0;
  priority_queue<P,vector<P>,greater<P> > que;
  que.push(P(0,0));
  while(!que.empty()) {
    P p=que.top();que.pop();
    int x=p.second,cc=p.first;
    if(d[x]<cc) continue;
    for(int i=0; i<v[x].size(); i++) {
      int y=v[x][i].first,c=v[x][i].second;
      if(d[y]>c&&d[x]<=c) {
        d[y]=c;
        que.push(P(c,y));
      }
    }
  }
  int ans=-1;
  for(int i=0; i<g.size(); i++) {
    int x=g[i].first,c=g[i].second;
    if(d[x]<=c) ans=max(ans,c);
  }
  cout << ans << endl;
  return 0;
}
