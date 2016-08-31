#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
vector<int> v[111111];
int d[111111],c[111111],D;
    
P visit(int p,int x,int z) {
  d[x]=z;
  P r(0,x);
  for(int i=0; i<v[x].size(); i++) {
    int y=v[x][i];
    if(y==p) continue;
    P t=visit(x,y,z+1);
    t.first++;
    if(r.first<t.first) r=t;
  }
  return r;
}
int diameter() {
  P r=visit(-1, 1,0);
  P t=visit(-1,r.second,0);
  D=t.first;
  return t.second;
}

int main() {
  int n;
  cin >> n;
  for(int i=0,x,y; i<n-1; i++) {
    cin >> x >> y;
    x--,y--;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  int x=diameter();
  queue<int> que;
  que.push(x);
  c[x]=(n-1)*2-D;
  while(!que.empty()) {
    x=que.front();que.pop();
    for(int i=0; i<v[x].size(); i++) {
      int y=v[x][i];
      if(c[y]) continue;
      if(d[x]>d[y]&&D/2<=d[y]) c[y]=c[x]+(D%2&&D/2==d[y]?0:1);
      else c[y]=c[x]-1;
      que.push(y);
    }
  }
  for(int i=0; i<n; i++) cout << c[i] << endl;
  return 0;
}
