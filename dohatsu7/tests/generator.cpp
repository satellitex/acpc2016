#include<bits/stdc++.h>
#include "testlib.h"
using namespace std;

struct data{
  int a,b,c;
  bool operator == (const data &p)const{
    return (a==p.a&&b==p.b&&c==p.c);
  }
  bool operator < (const data &p)const{
    if(a!=p.a)return a<p.a;
    if(b!=p.b)return b<p.b;
    return c<p.c;
  }
};

#define N 200



vector<int> X,Y;

int change(int id){
  return Y[id];
}

void init(){
  std::mt19937 MT( (int)time(0) );
  Y.clear();
  for(int i=0;i<=N;i++){
    Y.push_back(i);
  }
  shuffle( Y.begin()+2, Y.end()-1, MT );
}

void start(int ID){
  ofstream of( format("03_random_%02d.in", ID).c_str() );
  
  std::mt19937 mt( (int)time(0) );
  std::uniform_int_distribution<> randA(1,N-1);
  std::uniform_int_distribution<> randB(1,N);
  std::uniform_int_distribution<> randbb(0,5);
  int len = randbb(mt) * 10 + 5;
  
  std::uniform_int_distribution<> randC(1,len*10+10);
  

  set< data > st;

  for(int i=1;i<=len;i++){
    data d=(data){i,i+1, i*10 };
    st.insert(d);
  }
  
  for(int i=0;i<N*10;i++){
    int from=randA( mt );
    int to=randB(mt);
    if(from==to)continue;
    st.insert( (data){from,to, randC(mt) } );
  }
  
  of<<N<<' '<<st.size()<<endl;
  for( data d : st ){
    d.a=change(d.a);
    d.b=change(d.b);
    of<<d.a<<' '<<d.b<<' '<<d.c<<endl;
  }
  of.close();
}

int main(){
  for(int i=0;i<20;i++){
    init();
    start(i);
  }
  return 0;
}
