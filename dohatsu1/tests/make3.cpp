#include<bits/stdc++.h>
using namespace std;

string i2s(int i){
  stringstream ss;
  ss<<i;
  string res;
  ss>>res;
  return res;
}

int N = 5100; 

std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(0,17);
std::uniform_int_distribution<> randB(0,4);
string tmp="0123cdef";
vector<string> vec;


void solve(int ID){

  ofstream fout ( "m3random"+ i2s(ID) +".in" );
  set<string> st;


  shuffle( vec.begin() , vec.end() , mt );
  fout<<N<<endl;
  for(int i=0;i<N;i++)
    fout<< vec[i] <<endl;

  fout.close();
}

string s="xxxxx";
void dfs(int x,int f){
  if(x==5){
    if(f==1)vec.push_back(s);
  }else{
    for(int i=0;i<8;i++){
      if(f==1 && i%2==0)continue;
      s[x]=tmp[i];
      int nf=f;
      if(i%2==0)nf=1;
      dfs(x+1,nf);
    }
  }
}

int main(){
  dfs(0,0);
  for(int i=0;i<4;i++){
    solve(i);
  }
  return 0;
}
