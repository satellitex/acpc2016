#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

string i2s(int ID){
  char str[100];
  sprintf(str,"random%02d.in",ID);
  return string(str);
}

std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(0,25);


void solve(int ID){
  ofstream fout ( i2s(ID) );
  string str="";
  for(int i=0;i<100;i++){
    char ch='a'+ randA(mt);
    str+=ch;
    str+=ch;
  }

  if( randA(mt) <=10 ){
    str+='a';
    str+='z';
  }
  
  shuffle( str.begin() , str.end() , mt );
  
  fout<<str<<endl;
  fout.close();
}

int main(){
  for(int i=0;i<10;i++){
    solve(i);
  }
  return 0;
}
