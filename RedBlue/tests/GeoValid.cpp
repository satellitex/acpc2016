#include<bits/stdc++.h>
using namespace std;
#define MAX_V 105
#define INF 1000000001
typedef pair< double ,int> Pair;

typedef complex<double> P;
  
double eps=1e-10;

bool eq(double a,double b){
  return (-eps < a-b && a-b <eps);
}

bool eq(P a,P b){
  return ( eq(a.real(),b.real()) && eq(a.imag(),b.imag() ) );
}

double Sqrt(double x){
  return sqrt(max(0.0,x));
}

double dot(P a,P b){
  return real( b*conj(a) );
}

double cross(P a,P b){
  return imag( b*conj(a) );
}


P getcrosspoint(P a,P b,P c,P d){
  a-=d;b-=d;c-=d;
  return d+a+(b-a)*imag(a/c)/imag(a/c-b/c);
}
  
struct S{
  P p,q;
  S(P p,P q):p(p),q(q){}
};
  
struct C{
  P p;
  double r;
  C(P p,double r):p(p),r(r){}
  C(double x,double y,double r):p(P(x,y)),r(r){}
};

double getDistance(S a,P b){
  if( dot(b-a.p , a.q-a.p) < 0 )return abs(a.p-b);
  if( dot(b-a.q , a.p-a.q) < 0 )return abs(a.q-b);
  return abs( cross( a.p-a.q,b-a.q) / abs(a.p-a.q) );
}
 
void getTangent(C a,P p,vector<S> &res){
  P base=a.p-p;
  double w=Sqrt(norm(base)-a.r*a.r);
  P s=p+base*P(w,a.r)/norm(base)*w;
  P t=p+base*P(w,-a.r)/norm(base)*w;

  res.push_back( (S){p,s} );
  res.push_back( (S){p,t} );
}

int getState(C a,S b){
  double dist=getDistance(b,a.p);

  if(a.r-eps-eps<dist)return 1;
  return 0;
}

bool isParallel(S a,S b){
  P A=a.p-a.q;
  P B=b.p-b.q;
  return eq(0, cross(A,B) );
}

int n;
int SI,TI;
P a[105],b[105];


int main(){
  cin>>n;
  
  double x,y,r;
  cin>>x>>y>>r;
  C ca(x,y,r);
  
  cin>>x>>y>>r;
  C cb(x,y,r);

  double distCC=abs(ca.p-cb.p)-ca.r-cb.r;
  assert( (1e-3) < distCC );
  
  for(int i=0;i<n;i++){
    cin>>x>>y;
    a[i]=P(x,y);
    double distA=abs(ca.p-a[i])-ca.r;
    double distB=abs(cb.p-a[i])-cb.r;
    assert( (1e-3) < distA );
    assert( (1e-3) < distB );
  }
  
  for(int i=0;i<n;i++){
    cin>>x>>y;
    b[i]=P(x,y);
    double distA=abs(ca.p-b[i])-ca.r;
    double distB=abs(cb.p-b[i])-cb.r;
    assert( (1e-3) < distA );
    assert( (1e-3) < distB );    
  }
  

  return 0;
}
