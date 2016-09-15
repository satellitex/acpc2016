#include<bits/stdc++.h>
using namespace std;
#define MAX_V 6050
vector<string> v2,ans;
set<string> sv;
map<string,int> m;
void addV(string s){
  sv.insert(s);
  for(int i=0;i<5;i++){
    if((('0'<=s[i]&&s[i]<='9')&&(s[i]-'0')%2==0)||
       (('a'<=s[i]&&s[i]<='f')&&(s[i]-'a')%2==0)){
      if(s[i]=='0') {
	s[i]='f';v2.push_back(s);m[s]++;s[i]='0';
      }else if(s[i]=='a') {
	s[i]='9';v2.push_back(s);m[s]++;s[i]='a';
      }else{
	s[i]--;v2.push_back(s);m[s]++;s[i]++;
      }
      s[i]++;v2.push_back(s);m[s]++;s[i]--;
    }
  }
}

int V;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V],lr[MAX_V];
void add_edge(int u,int v){
  G[u].push_back(v);
  G[v].push_back(u);
}

bool check(string s1,string s2){
  int c=0,idx=-1;
  for(int i=0;i<5;i++)
    if(s1[i]==s2[i]) c++;
    else idx=i;
  if(c!=4) return false;
  if(s1[idx]=='9'){
    if(s2[idx]=='b') return true;
    return false;
  }
  if(s1[idx]=='1'&&s2[idx]=='f') return true;
  if(s2[idx]-s1[idx]==2) return true;
  return false;
}

string getE(string s1,string s2){
  int idx;
  string res=s1;
  for(int i=0;i<5;i++) if(s1[i]!=s2[i]) idx=i;
  if(s1[idx]=='1'&&s2[idx]=='f') res[idx]='0';
  return res;
}

bool exE(string s1,string s2){
  int idx;
  string res=s1;
  for(int i=0;i<5;i++) if(s1[i]!=s2[i]) idx=i;
  if(s1[idx]=='1'&&s2[idx]=='f') res[idx]='0';
  else if(res[idx]=='9') res[idx]='a';
  else res[idx]++;
  return sv.find(res)!=sv.end();
}

void addE(){
  bool er[MAX_V]={};
  for(int i=0;i<v2.size();i++){
    for(int j=i+1;j<v2.size();j++){
      if(er[i]||er[j]) continue;
      if(check(v2[i],v2[j])){
	if(m[v2[i]]==1&&m[v2[j]]==1&&exE(v2[i],v2[j])) {
	  ans.push_back(getE(v2[i],v2[j]));
	  er[i]=er[j]=true;
	}
      }
    }
  }
  vector<string> nv(v2);
  v2.clear();
  for(int i=0;i<nv.size();i++){
    if(!er[i]) v2.push_back(nv[i]);
  }
  for(int i=0;i<v2.size();i++){
    for(int j=i+1;j<v2.size();j++){
      if(check(v2[i],v2[j])&&exE(v2[i],v2[j])){
	add_edge(i,j);
      }
    }
  }
}

bool dfs(int v){
  used[v]=true;
  for(int i=0;i<G[v].size();i++){
    int u=G[v][i],w=match[u];
    if(w<0||!used[w]&&dfs(w)){
      match[v]=u;
      match[u]=v;
      return true;
    }
  }
  return false;
}

int bipartite_matching(){
  int res=0;
  memset(match,-1,sizeof(match));
  for(int v=0;v<V;v++){
    if(match[v]<0){
      memset(used,0,sizeof(used));
      if(dfs(v)){
	res++;
      }
    }
  }
  return res;
}

void setLR(int v,bool b){
  if(used[v]) return;
  used[v]=true;lr[v]=b;
  for(int i=0;i<G[v].size();i++){
    setLR(G[v][i],!b);
  }
}


void addM(int v){
  if(v==-1) return;
  if(used[v]) return;
  used[v]=true;
  if(lr[v]) {
    ans.push_back(v2[v]);
    addM(match[v]);
  }else{
    for(int i=0;i<G[v].size();i++){
      addM(G[v][i]);
    }
  }
}

void addA(){
  memset(used,0,sizeof(used));
  for(int i=0;i<V;i++){
    if(!lr[i]&&match[i]<0){
      addM(i);
    }
  }
  for(int i=0;i<V;i++){
    if(!lr[i]&&!used[i]) {
      ans.push_back(v2[i]);
    }
  }
}

int main(){
  int n,i,j,k;
  string s;
  cin>>n;
  for(i=0;i<n;i++){
    cin >> s;
    addV(s);
  }
  sort(v2.begin(),v2.end());
  v2.erase(unique(v2.begin(),v2.end()),v2.end());
  addE();
  V=v2.size();
  int base=bipartite_matching();
  memset(used,0,sizeof(used));
  for(i=0;i<V;i++) sort(G[i].begin(),G[i].end());
  for(i=0;i<V;i++) if(!used[i]) setLR(i,0);
  addA();
  sort(ans.begin(),ans.end());
  cout << ans.size() << endl;
  for(i=0;i<ans.size();i++){
    cout << ans[i] << endl;
  }
  return 0;
}
