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

#define N 10

std::mt19937 mt( (int)time(0) );
std::uniform_int_distribution<> randA(1,N-1);
std::uniform_int_distribution<> randB(1,N);
std::uniform_int_distribution<> randC(0,2*N);

int G[N+1][N+1];
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
  
  int T=randA(mt);
  vector<data> v;
  for(int i=0;i<T;i++){
    int a=i+1;
    int b=a+1;
    int c=(i+1)*2;
    //    if( randB(mt) %2==0&&i+1==T)b=N;
    v.push_back( (data){a,b,c} );
  }



  for(int i=0;i<10;i++){
    int a=randA(mt);
    int b=randB(mt);
    int c=randC(mt);
    if(a==b || c==0)continue;
    v.push_back( (data){a,b,c} );
  }

  sort(v.begin(),v.end());

  v.erase( unique(v.begin(),v.end()) , v.end() );
  

  
  cout<<N<<' '<<v.size()<<endl;
  for(data d : v ){
    d.a=change(d.a);
    d.b=change(d.b);
    cout<<d.a<<' '<<d.b<<' '<<d.c<<endl;
  }

}

int main(){
  solve();  
  return 0;
}
