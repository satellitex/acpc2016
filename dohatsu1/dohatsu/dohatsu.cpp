#include<bits/stdc++.h>
using namespace std;
#define MAX_V 3000

vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];
bool flag[MAX_V];

void add_edge(int u,int v){
  G[u].push_back(v);
  G[v].push_back(u);
}
 
bool dfs(int v){
  if( flag[v] )return false;
  
  used[v]=true;
  for(int i=0;i<(int)G[v].size();i++){
    int u=G[v][i],w=match[u];
    if( flag[u] )continue;
    if( w<0 ||( !used[w] && dfs(w) )){
      match[v]=u;
      match[u]=v;
      return true;
    }
  }
  return false;
}
 
int bipartite_matching(bool flg=true){
  if(flg)memset(match,-1,sizeof(match));
  int res=0;
  for(int v=0;v<MAX_V;v++){
    if(match[v]<0){
      memset( used, false, sizeof(used) );
      if(dfs(v)){
        res++;
      }
    }
  }
  return res;
}
 

int N;
map<string,int> mp,mA,mB;
vector<string> vec;

string tmp="0123456789abcdef";
string change(string str,int flg){
  if(flg==0)return str;
  for(int i=0;i<4;i++){
    int num=tmp.find(str[i]);
    if(num%2==1)continue;
    if(flg==1)str[i]=tmp[(num+1)%16];
    if(flg==2)str[i]=tmp[(num+15)%16];
    return str;
  }
}

void add_edge(string s){
  string a=change(s,1);
  string b=change(s,2);
  int ia,ib;
  if(mp.count(a)==0)mp[a]=mp.size();
  ia=mp[a];
  if(mp.count(b)==0)mp[b]=mp.size();
  ib=mp[b];
  mA[s]=ia;
  mB[s]=ib;
  add_edge(ia,ib);
  vec.push_back(s);
  vec.push_back(a);
  vec.push_back(b);
}

void erase( vector<int> &v , int key ){
  vector<int> nv;
  for(int i=0;i<(int)v.size();i++)
    if(v[i]!=key)nv.push_back(v[i]);
  v=nv;
}

int main(){
  cin>>N;
  for(int i=0;i<N;i++){
    string s;
    cin>>s;
    add_edge(s);
  }
  
  int ans=bipartite_matching();
  cout<<ans<<endl;
  
  sort(vec.begin(),vec.end());
  vec.erase( unique(vec.begin(),vec.end()) , vec.end() );

  for(int i=0;i<(int)vec.size();i++){
    string str=vec[i];
    
    if(mp.count(str)){
      int id=mp[str];
      if(match[id]==-1)continue;
      int target=match[id];
      match[id]=match[target]=-1;

      flag[id]=true;
      memset(used, false, sizeof(used));
      if( dfs(target)==false )cout<<str<<endl;
      else flag[id]=false;
      
    }else{
      int ia=mA[str];
      int ib=mB[str];
      if(match[ia]!=ib)continue;
      if(match[ib]!=ia)continue;
      erase(G[ia],ib);
      erase(G[ib],ia);
      match[ia]=-1;
      match[ib]=-1;

      memset(used, false, sizeof(used));
      if( dfs(ia)==false ){
        cout<<str<<endl;
        continue;
      }
      
      memset(used, false, sizeof(used));
      if( dfs(ib)==false ){
        cout<<str<<endl;
        continue;
      }
      
      G[ia].push_back(ib);
      G[ib].push_back(ia);
    }
  }
  return 0;
}

