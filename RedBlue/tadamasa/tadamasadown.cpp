#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace std;
#define MAX_V 205
#define INF 1000000001
namespace mp = boost::multiprecision;

typedef mp::cpp_dec_float_100 ld;

typedef pair< ld ,int> Pair;
 
struct edge {
  int to;
  int cap;
  int rev;
  ld cost;
};
 
int V;
vector<edge> G[MAX_V];
ld h[MAX_V];
ld dist[MAX_V];
int prevv[MAX_V],preve[MAX_V];
 
void init_edge(){
  for(int i=0;i<MAX_V;i++)G[i].clear();
}
 
void add_edge(int from,int to,int cap,ld cost){
  G[from].push_back((edge){to,cap,(int)G[to].size(),cost});
  G[to].push_back((edge){from,0,(int)G[from].size()-1,-cost});
}
 
ld min_cost_flow(int s,int t,int f){
  ld eps = 0.0000000001f;
  ld res = 0;
  fill(h,h+V,0.0);
   
  while(f>0){
     
    priority_queue< Pair, vector<Pair>, greater<Pair> >  que;
    fill( dist, dist+V , (ld)INF );
    dist[s]=0;
    que.push(Pair(0,s));
 
    fill ( prevv , prevv + V , s );
     
    while(!que.empty()){
      Pair p = que.top(); que.pop();
      int v = p.second;
      if(dist[v]+eps < p.first)continue;
      for(int i=0;i<(int)G[v].size();i++){
        edge &e = G[v][i];
        if(e.cap>0&&dist[e.to] > eps+dist[v]+e.cost+h[v]-h[e.to]){
          dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
          prevv[e.to]=v;
          preve[e.to]=i;
          que.push(Pair(dist[e.to],e.to));
        }
      }
    }
 
         
    if(dist[t] == INF){
      return -1;
    }
    
    for(int v=0;v<V;v++)h[v]+=dist[v]; 
 
    int d=f;
    for(int v=t;v!=s;v=prevv[v]){
      d=min(d,G[prevv[v]][preve[v]].cap);
    }
    assert( d > 0 );
    f-=d;
 
    res+=d*h[t];
 
    for(int v=t;v!=s;v=prevv[v]){
      edge &e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
 
  }
  return res;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef complex<ld> P;
  
ld eps(std::string("0.000000000001"));

bool eq(ld a,ld b){
  return (-eps < a-b && a-b <eps);
}

bool eq(P a,P b){
  return ( eq(a.real(),b.real()) && eq(a.imag(),b.imag() ) );
}

ld Sqrt(ld x){
  
  return sqrt( abs(x) );
}

ld dot(P a,P b){
  return real( b*conj(a) );
}

ld cross(P a,P b){
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
  ld r;
  C(P p,ld r):p(p),r(r){}
  C(ld x,ld y,ld r):p(P(x,y)),r(r){}
};

ld getDistance(S a,P b){
  if( dot(b-a.p , a.q-a.p) < 0 )return abs(a.p-b);
  if( dot(b-a.q , a.p-a.q) < 0 )return abs(a.q-b);
  return abs( cross( a.p-a.q,b-a.q) / abs(a.p-a.q) );
}
 
void getTangent(C a,P p,vector<S> &res){
  P base=a.p-p;
  ld w=Sqrt(norm(base)-a.r*a.r);
  P s=p+base*P(w,a.r)/norm(base)*w;
  P t=p+base*P(w,-a.r)/norm(base)*w;

  res.push_back( (S){p,s} );
  res.push_back( (S){p,t} );
}

int getState(C a,S b){
  ld dist=getDistance(b,a.p);

  if(a.r-eps-eps<dist)return 1;
  return 0;
}

bool isParallel(S a,S b){
  P A=a.p-a.q;
  P B=b.p-b.q;
  return eq(0, cross(A,B) );
}

ld getCost(P a,P b,C c,C d,bool debug=false){
  
  if( getState(c,S(a,b)) == 1 && getState(d,S(a,b)) == 1 ){
    return abs(a-b);
  }
  
  vector< S > va,vb,tmp;
  getTangent(c,a,va);
  getTangent(d,a,va);
  getTangent(c,b,vb);
  getTangent(d,b,vb);


  ld res=1e20;
  
  for(int i=0;i<(int)va.size();i++){
    for(int j=0;j<(int)vb.size();j++){
      S as=va[i];
      S bs=vb[j];
      if( isParallel(as,bs) )continue;
      P target=getcrosspoint(as.p, as.q, bs.p, bs.q);
      /*
      if(debug){
        cout<<as.p<<' '<<as.q<<' '<<bs.p<<' '<<bs.q<<endl;
      }
      */
      
      if( getState(c, S(a,target)) !=1 )continue;
      if( getState(c, S(b,target)) !=1 )continue;
      if( getState(d, S(a,target)) !=1 )continue;
      if( getState(d, S(b,target)) !=1 )continue;

      ld total = abs(target-a)+abs(target-b);
      res=min(res, total);
    }
  }

  return res;
}

int n;
int SI,TI;
P a[105],b[105];


int main(){
  cin>>n;

  ld downx=0.000000001f;
  
  ld x,y,r;
  cin>>x>>y>>r;

  r-=downx;
  
  C ca(x,y,r);
  
  cin>>x>>y>>r;

  r-=downx;
    
  C cb(x,y,r);
  

  SI=n+n;
  TI=SI+1;
  V=TI+1;

  
  for(int i=0;i<n;i++){
    cin>>x>>y;
    a[i]=P(x,y);
  }
  
  for(int i=0;i<n;i++){
    cin>>x>>y;
    b[i]=P(x,y);
  }
  
  for(int i=0;i<n;i++){
    add_edge(SI,i,1,0);
    add_edge(n+i,TI,1,0);
    for(int j=0;j<n;j++){
      ld cost=getCost(a[i],b[j],ca,cb, i==0&&j==0);
      add_edge(i,n+j,1,cost);
    }
  }


  ld ans=min_cost_flow(SI,TI,n);
  if(ans<0){
    cout<<"Impossible"<<endl;
  }else{
    printf("%.10f\n",(double)ans);
  }
  return 0;
}
