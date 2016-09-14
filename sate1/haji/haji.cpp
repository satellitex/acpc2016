#include <bits/stdc++.h>
#define N 100000
#define f first
#define s second
using namespace std;
typedef pair<int,int> P;
typedef pair<P,int> PP;
vector <int> G[N];
vector <PP> D[N];
int n;
bool used[N];

P dfs(int pos,int dep,int cnt){
  if(used[pos])return P(0,0);
  used[pos]=1;
  int ndep=0,ncnt=0;
  for(int i=0;i<(int)G[pos].size();i++){
    P res=dfs(G[pos][i],dep+1,cnt+1);
    res.f-=dep;
    D[pos].push_back(PP(res,G[pos][i]));
  }
  return P(dep+ndep,ncnt);
}

int calc(vector <PP> &a){
  sort(a.begin(),a.end());
  unique(a.begin(),a.erase(a.begin(),a.end()));
  int res=0;
  for(int i=0;i<(int)a.size()-1;i++)res+=a[i].f.f+a[i].f.s;
  return res+a.back().f.s;
}

int main(){
  cin>>n;
  for(int i=0,a,b;i<n-1;i++){
    cin>>a>>b;a--,b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  dfs2(0,0);
  dfs(start,0,0);
  
  for(int i=0;i<n;i++)cout << calc(D[i])<<endl;

  
    return 0;
}
