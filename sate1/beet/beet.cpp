#include<bits/stdc++.h>
using namespace std;
int n,idx[3];
int d[3][100050];
bool u[100050];
vector<int> v[100050];
void dfs(int x,int p,int w){
  d[w][p]=x;u[p]=true;
  if(d[w][p]>d[w][idx[w]]) idx[w]=p;
  for(int i=0;i<v[p].size();i++) if(!u[v[p][i]]) dfs(x+1,v[p][i],w);
}
void calc(){
  
}
int main(){
  cin>>n;
  int i,j,k;
  for(i=0;i<n-1;i++){
    cin>>j>>k;
    j--;k--;
    v[j].push_back(k);
    v[k].push_back(j);
  }
  idx[0]=idx[1]=idx[2]=0;
  memset(d,0,sizeof(d));
  memset(u,0,sizeof(u));
  dfs(0,0,0);
  memset(u,0,sizeof(u));
  dfs(0,idx[0],1);
  memset(u,0,sizeof(u));
  dfs(0,idx[1],2);
  for(i=0;i<n;i++){
    //cout << d[1][i] << ":" << d[2][i] << endl;
    cout << 2*(n-1) - max(d[1][i],d[2][i]) << endl;
  }
  return 0;
}
