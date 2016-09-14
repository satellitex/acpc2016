#include<bits/stdc++.h>
using namespace std;

string i2s(int i){
  stringstream ss;
  ss<<i;
  string res;
  ss>>res;
  return res;
}

int N = 3000; 

std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(0,17);
std::uniform_int_distribution<> randB(0,4);
string tmp0="02468ace00000eeeee";
string tmp1="13579bdf11111fffff";



void solve(int ID){
  if(ID<=5)N=3000;
  else N=3000-ID;
  
  
  vector<string> vec;
  ofstream fout ( "random"+ i2s(ID) +".in" );
  
  set<string> st;
  
  for(int i=0;i<N;i++){
    string str="";
    int target=randB( mt );
    
    for(int j=0;j<5;j++){
      if(j==target) str+=tmp0[ randA(mt) ];
      else str+=tmp1[ randA(mt) ];
    }

    
    if(st.count(str)>0)continue;
    st.insert(str);
    vec.push_back(str);
  }

  fout<<vec.size()<<endl;
  for(int i=0;i<(int)vec.size();i++)
    fout<< vec[i] <<endl;

  fout.close();
}

int main(){
  for(int i=0;i<14;i++){
    solve(i);
  }
  return 0;
}
