#include<bits/stdc++.h>
using namespace std;

int N,M,L;
vector<int> G[5][8];
vector<int> g[5][8];

int mem[5][8][301];

int rec(int x,int y,int z){
  if(z==L)return 0;
  if(x==5)return 0;
  if(y==N)return rec(x+1,0,z);
  if(mem[x][y][z]!=-1)return mem[x][y][z];
  int res=rec(x,y+1,z);
  for(int i=0;i<(int)G[x][y].size();i++){
    int to=G[x][y][i];
    int cnt=g[x][y][i];
    res=max(res, rec(x,y+to,z+1)+cnt);
  }
  return mem[x][y][z]=res;
}

int main(){
  memset(mem,-1,sizeof(mem));
  cin>>N>>M>>L;
  for(int i=0;i<M;i++){
    int d,a,k,t;
    cin>>d>>a>>k>>t;
    a--;
    G[d][a].push_back(k);
    g[d][a].push_back(t);
  }
  cout<< rec(0,0,0) <<endl;
  
  return 0;
}
