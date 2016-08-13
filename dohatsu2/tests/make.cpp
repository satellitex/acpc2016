#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

#define H 16
#define W 16


std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randW(0,W-1);
std::uniform_int_distribution<> randH(0,H-1);
std::uniform_int_distribution<> randA(3,4);


void solveH(){
  cout<<H<<' '<<1<<endl;
  vector< char > v(H);
  v[ randH(mt) ]='@';
  for(int i=0;i<H;i++){
    if(v[i]!='@'){
      if( randH(mt)%4==0 )v[i]='o';
      else v[i]='.';
    }

    cout<<v[i]<<endl;
  }
}

void solveW(){
  cout<<1<<' '<<W<<endl;
  vector< char > v(W);
  
  v[ randW(mt) ]='@';
  for(int i=0;i<W;i++){
    if(v[i]!='@'){
      if( randW(mt)%4==0 )v[i]='o';
      else v[i]='.';
    }
    cout<<v[i];
  }
  cout<<endl;
}

void solve(int size){
  vector<P> v;
  
  for(int i=0;i<H;i++)
    for(int j=0;j<W;j++)
      v.push_back(P(i,j));
  shuffle( v.begin() , v.end() , mt );
  cout<<H<<' '<<W<<endl;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      char ch='.';
      
      for(int k=0;k<size;k++)
        if(P(i,j)==v[k])ch='o';
      
      if(P(i,j)==v[size])ch='@';
      cout<<ch;
    }
    cout<<endl;
  }
}

int main(){
  
  solve( randA(mt) );

  return 0;
}
