#include<bits/stdc++.h>
using namespace std;
typedef vector<char> vec;
typedef vector<vec> mat;

int dy[]={-1,0,1,0};
int dx[]={0,1,0,-1};

int H,W,ty,tx;
int cnt=0;

mat t;

mat func(mat s,int y,int x,int dir){
  while(1){
    int ny=y+dy[dir];
    int nx=x+dx[dir];
    if(ny<0 || nx<0)break;
    if(ny>=H || nx>=W)break;
    swap(s[y][x],s[ny][nx]);
    y=ny;
    x=nx;
  }
  return s;
}

bool solve(){
  if(cnt>=3 && H>1 && W>1)return true;
  queue< mat > Q;
  map< mat , bool > d;
  Q.push(t);
  d[t]=true;
  while(!Q.empty()){
    mat s=Q.front();Q.pop();

    if(s[ty][tx]=='o')return true;
    for(int i=0;i<H;i++){
      for(int j=0;j<W;j++){
        if(s[i][j]=='.')continue;
        for(int k=0;k<4;k++){
          mat next=func(s,i,j,k);
          if(d.count(next)>0)continue;
          d[next]=true;
          Q.push(next);
        }
      }
    }
  }
  return false;
}

int main(){
  cin>>H>>W;
  t.resize(H);
  for(int i=0;i<H;i++){
    t[i].resize(W);
    for(int j=0;j<W;j++){
      cin>>t[i][j];
      if(t[i][j]=='o')cnt++;
      if(t[i][j]=='@'){
        ty=i;
        tx=j;
        t[i][j]='.';
      }
    }
  }
  cout<< (solve()?"yes":"no") <<endl;
  return 0;
}
