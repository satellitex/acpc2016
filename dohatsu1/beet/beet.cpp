#include<bits/stdc++.h>
using namespace std;
#define MAX_V 6050
typedef pair<string,bool> B;
typedef pair<int,int> P;
vector<string> v1,v2,ans;
vector<B> v3;
set<string> sv;
map<string,int> m,mv,me;
map<P,int> ok;
void addV(string s){
  sv.insert(s);
  v1.push_back(s);
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

int V,base,cur;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V],lr[MAX_V],er[MAX_V],erv[MAX_V],rm[MAX_V],rme[MAX_V];
void add_edge(int u,int v){
  G[u].push_back(v);
  G[v].push_back(u);
}

bool erV(string s){
  string s1,s2;
  for(int i=0;i<5;i++){
    if((('0'<=s[i]&&s[i]<='9')&&(s[i]-'0')%2==0)||
       (('a'<=s[i]&&s[i]<='f')&&(s[i]-'a')%2==0)){
      if(s[i]=='0') {
	s[i]='f';s1=s;s[i]='0';
      }else if(s[i]=='a') {
	s[i]='9';s1=s;s[i]='a';
      }else{
	s[i]--;s1=s;s[i]++;
      }
      s[i]++;s2=s;s[i]--;
    }
  }
  if(m[s1]==1&&m[s2]==1){
    er[mv[s1]]=er[mv[s2]]=true;
    ans.push_back(min(s,min(s1,s2)));
    return true;
  }
  return false;
}

void mkG(string s){
  string s1,s2;
  for(int i=0;i<5;i++){
    if((('0'<=s[i]&&s[i]<='9')&&(s[i]-'0')%2==0)||
       (('a'<=s[i]&&s[i]<='f')&&(s[i]-'a')%2==0)){
      if(s[i]=='0') {
	s[i]='f';s1=s;s[i]='0';
      }else if(s[i]=='a') {
	s[i]='9';s1=s;s[i]='a';
      }else{
	s[i]--;s1=s;s[i]++;
      }
      s[i]++;s2=s;s[i]--;
    }
  }
  ok[P(mv[s1],mv[s2])]=ok[P(mv[s2],mv[s1])]=me[s];
  add_edge(mv[s1],mv[s2]);
}

void addE(){
  memset(er,0,sizeof(er));
  memset(erv,0,sizeof(erv));
  for(int i=0;i<v2.size();i++) mv[v2[i]]=i;
  for(int i=0;i<v1.size();i++) erv[i]=erV(v1[i]);
  vector<string> nv1(v1);
  v1.clear();
  for(int i=0;i<nv1.size();i++) if(!erv[i]) v1.push_back(nv1[i]);
  vector<string> nv2(v2);
  v2.clear();
  for(int i=0;i<nv2.size();i++) if(!er[i]) v2.push_back(nv2[i]);
  for(int i=0;i<v2.size();i++){
    mv[v2[i]]=i;
    v3.push_back(B(v2[i],true));
  }
  for(int i=0;i<v1.size();i++){
    me[v1[i]]=i;
    mkG(v1[i]);
    v3.push_back(B(v1[i],false));
  }
  sort(v3.begin(),v3.end());
}

bool dfs(int v){
  used[v]=true;
  for(int i=0;i<G[v].size();i++){
    int u=G[v][i],w=match[u];
    if(rm[u]) continue;
    if(rme[ok[P(u,v)]]) continue;
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
    if(rm[v]) continue;
    if(match[v]<0){
      memset(used,0,sizeof(used));
      if(dfs(v)){
	res++;
      }
    }
  }
  return res;
}

void addA(){
  memset(rm,0,sizeof(rm));
  memset(rme,0,sizeof(rme));
  for(int i=0;i<v3.size();i++){
    //cout << v3[i].first << ":" << base << ":";
    if(v3[i].second){
      rm[mv[v3[i].first]]=true;
      cur=bipartite_matching();
      if(base-cur==1)
	ans.push_back(v3[i].first),base=cur;
      else
	rm[mv[v3[i].first]]=false;
    }else{
      rme[me[v3[i].first]]=true;
      cur=bipartite_matching();
      if(base-cur==1)
	ans.push_back(v3[i].first),base=cur;
      else
	rme[me[v3[i].first]]=false;
    }
    //cout << cur << endl;
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
  base=bipartite_matching();
  //cout << base << endl;
  addA();
  sort(ans.begin(),ans.end());
  cout << ans.size() << endl;
  for(i=0;i<ans.size();i++){
    cout << ans[i] << endl;
  }
  return 0;
}
