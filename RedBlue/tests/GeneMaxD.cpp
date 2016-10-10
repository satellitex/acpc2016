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
std::uniform_int_distribution<> randA(1,200);



void solve(int ID){
  ofstream fout ( "3_randomD_"+ i2s(ID) +".in" );

  int N=100;
  
  fout<<N<<endl;
  
  fout<<35<<' '<<35<<' '<<49<<endl;
  fout<<-5<<' '<<-5<<' '<<7<<endl;

  map<int, map<int,int> > mp;

  fout<< -1000 <<' '<< 1000 <<endl;
  
  for(int i=0;i<N+N-2;i++){
    while(1){
      int x=randA(mt)-100;
      int y=randA(mt)-100;
       
      if(mp[x][y])continue;
      if( (x-35)*(x-35) + (y-35)*(y-35) <= 49*49 )continue;
      if( (x+5)*(x+5) + (y+5)*(y+5) <= 7*7 )continue;
      
      mp[x][y]=true;
      fout<<x<<' '<<y<<endl;
      break;
    }
  }
  
  fout<< 1000 <<' '<< -1000 <<endl;
  
  fout.close();
}

int main(){
  for(int i=1;i<=3;i++){
    solve(i);
  }
  return 0;
}
