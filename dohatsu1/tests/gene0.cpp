#include<bits/stdc++.h>
using namespace std;

string i2s(int i){
  stringstream ss;
  ss<<i;
  string res;
  ss>>res;
  return res;
}

int N = 6000; 

std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(0,17);
std::uniform_int_distribution<> randB(0,4);
string tmp="0123456789abcdef";
vector<string> vec,t;


string change(string str,int flg){
  string tmp="0123456789abcdef";
  if(flg==0)return str;
  for(int i=0;i<(int)str.size();i++){
    int num=tmp.find(str[i]);
    if(num%2==1)continue;
    if(flg==1)str[i]=tmp[(num+1)%16];
    if(flg==2)str[i]=tmp[(num+15)%16];
    return str;
  }
}

void solve(int ID){

  ofstream fout ( "hand"+ i2s(ID) +".in" );
  set<string> st;


  shuffle( vec.begin() , vec.end() , mt );
  for(int i=0;i<(int)vec.size();i++){
    if(vec[i][0]!='0')continue;
    if(vec[i][1]!='7')
      if(vec[i][2]!='7')
        if(vec[i][3]!='7')
          if(vec[i][4]!='7')
            t.push_back(vec[i]);
  }

  map<string,bool> mp;
  for(int i=0;i<(int)t.size();i++){
    string str=t[i];
    mp[  change(str ,1) ]=true;
    mp[  change(str ,2) ]=true;
  }

  for(int i=0;i<(int)vec.size();i++){
    string str=vec[i];
    if(str[0]=='0')continue;
    
    if( mp[ change(str ,1) ] )continue;
    if( mp[ change(str ,2) ] )continue;

    bool flg=true;

    for(int j=0;j<5;j++){
      if(str[j]<'5' || 'b' < str[j] )flg=false;
    }
    if(flg)t.push_back( vec[i] );

    if(t.size()==6000)break;
  }

  vec=t;
  //  sort(vec.begin(), vec.end());
  /*
  fout<<6000<<endl;
  for(int i=0;i<2000;i++){
    fout<< vec[i] <<endl;
    vec[i][0]='2';
    fout<< vec[i] <<endl;
    vec[i][0]='e';
    fout<< vec[i] <<endl;
  }
  */

  N=vec.size();
  
  fout<<N<<endl;
  for(int i=0;i<N;i++)
    fout<< vec[i] <<endl;

  fout.close();
}

string s="xxxxx";
void dfs(int x,int f){
  if(x==5){
    if(f==1){
      vec.push_back(s);
    }
  }else{

    for(int i=0;i<16;i++){
      int nf=f;
      if(i%2==0)nf++;
      if(nf>1)continue;
      s[x]=tmp[i];
      dfs(x+1,nf);
    }
  }
}

int main(){
  dfs(0,0);
  for(int i=0;i<1;i++){
    solve(i);
  }
  return 0;
}




