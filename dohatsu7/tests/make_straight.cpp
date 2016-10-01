#include<bits/stdc++.h>
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

#define N 100000

std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(1,N-1);
std::uniform_int_distribution<> randB(1,N);
std::uniform_int_distribution<> randC(0,2*N);

vector<int> X,Y;

int change(int id){
  if(id==1||id==N)return id;
  int target=lower_bound(X.begin(),X.end(),id)-X.begin();
  return Y[target];
}

void solve(){
  for(int i=2;i<=N-1;i++)X.push_back(i);
  Y=X;
  shuffle(Y.begin(),Y.end(), mt);
  
  vector< data > v;

  for(int i=1;i+1<=N;i++){
    v.push_back( (data){ i, i+1 , 1000000000 } );
  }

  cout<<N<<' '<<v.size()<<endl;

  //  shuffle( v.begin(), v.end() ,mt );
  reverse( v.begin(), v.end() );
  
  for(int i=0;i<(int)v.size();i++){
    data d=v[i];
    cout<< change(d.a) <<' '<< change(d.b) <<' '<<d.c<<endl;
  }
  
}

int main(){
  solve();  
  return 0;
}
