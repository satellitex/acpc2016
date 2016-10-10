#include<bits/stdc++.h>
using namespace std;

string i2s(int i){
  stringstream ss;
  ss<<i;
  string res;
  ss>>res;
  return res;
}


std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(1,100);



void solve(int ID){
  ofstream fout ( "3_randomA_"+ i2s(ID) +".in" );

  int N=100;
  
  fout<<N<<endl;
  
  fout<<-50<<' '<<50<<' '<<50<<endl;
  fout<<50<<' '<<-50<<' '<<50<<endl;

  map<int, map<int,int> > mp;
  
  for(int i=0;i<N;i++){
    while(1){
      int x=randA(mt);
      int y=randA(mt);
      if(i%10==0)x=-x,y=-y;
      if(mp[x][y])continue;
      mp[x][y]=true;
      fout<<x<<' '<<y<<endl;
      break;
    }
  }
  
  for(int i=0;i<N;i++){
    while(1){
      int x= -randA(mt);
      int y= -randA(mt);
      if(i%10==0)x=-x,y=-y;
      if(mp[x][y])continue;
      mp[x][y]=true;
      fout<<x<<' '<<y<<endl;
      break;
    }
  }
  fout.close();
}

int main(){
  for(int i=1;i<=3;i++){
    solve(i);
  }
  return 0;
}
