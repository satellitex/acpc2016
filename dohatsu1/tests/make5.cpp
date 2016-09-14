#include<bits/stdc++.h>
using namespace std;

std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(0,10);

string tmp="13579bd0";

vector<string> v;
string s="xxxxx";

void dfs(int x,int f){
  if(x==5){
    if(f==1)v.push_back(s);
  }else{
    for(int i=0;i<8;i++){
      if(f==1 && i==7)continue;
      s[x]=tmp[i];
      int nf=f;
      if(i==7)nf=1;
      dfs(x+1,nf);
    }
  }
}
int main(){
  
  dfs(0,0);  
  
  
  shuffle( v.begin() , v.end() , mt );

  cout<<3000<<endl;
  for(int i=0;i<3000;i++){
    cout<<v[i]<<endl;
  }
  return 0;
}
