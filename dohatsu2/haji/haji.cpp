#include <bits/stdc++.h>
using namespace std;
int h,w;
char mp[16][16];
vector<int> sx,sy;
int dx[]={0,0,1,-1};
int dy[]={-1,1,0,0};


int used[20][20][20][20];
int dfs(int x,int y,int a,int b){
  if(x<0)return 0;
  if(mp[y][x]=='@')return 1;
  if(used[y][x][max(0,b)][max(0,a)])return 0;
  used[y][x][max(0,b)][max(0,a)]=1;
  
  int res=0;
  for(int i=0;i<4;i++){
    int nx=x,ny=y,na=a,nb=b;
    while(1){
      int X=nx+dx[i],Y=ny+dy[i];
      if(X<0||Y<0||X>=w||Y>=h)break;
      if(X==a&&Y==b)na=nx,nb=ny;
      nx=X,ny=Y;
    }
    res|=dfs(nx,ny,na,nb);
  }
  return res|dfs(a,b,x,y);
}

int check(int x,int y,int dir){
  int cnt=0,cnt2=0;
  while(mp[y][x]!='@')cnt+=mp[y][x]=='o',x+=dx[dir],y+=dy[dir];
  while(x>=0&&y>=0&&x<w&&y<h&&mp[y][x]!='o')cnt2++,x+=dx[dir],y+=dy[dir];
  return cnt>=cnt2;  
}

bool check(){
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      if(mp[i][j]=='o')sx.push_back(j),sy.push_back(i);
  int n=sx.size();
  if(n>=3){
    if(h==1) return check(0,0,2)|check(w-1,0,3);
    if(w==1) return check(0,0,1)|check(0,h-1,0);
    return 1;
  }
  if(n==2) return dfs(sx[0],sy[0],sx[1],sy[1]);
  if(n==1) return dfs(sx[0],sy[0],-10000,-10000);
}

int main(){
  cin>>h>>w;
  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)cin>>mp[i][j];
  
  cout <<(check()? "yes":"no")<<endl;
  return 0;
}
