#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
int d[3333][3333],dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
bool check(int n,int m,int x,int y) {return x>=0&&x<n&&y>=0&&y<m;}

int main() {
  int n,m,k;
  cin >> n >> m >> k;
  for(int i=0; i<n; i++)for(int j=0; j<m; j++) d[i][j]=1<<29;
  queue<P> que;
  for(int i=0; i<k; i++) {
    int x,y;
    cin >> x >> y;
    d[x][y]=0;
    que.push(P(x,y));
  }
  while(!que.empty()) {
    P p=que.front();que.pop();
    for(int i=0; i<4; i++) {
      int x=p.first+dx[i],y=p.second+dy[i];
      if(check(n,m,x,y)&&d[x][y]==1<<29) {
        d[x][y]=d[p.first][p.second]+1;
        que.push(P(x,y));
      }
    }
  }
  int ans=0;
  for(int i=0; i<n; i++)for(int j=0; j<m; j++) ans=max(ans,d[i][j]);
  cout << ans << endl;
  return 0;
}
