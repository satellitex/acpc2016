#include<bits/stdc++.h>
using namespace std;
#define MAX_V 105
#define INF 1000000001
typedef pair< double ,int> Pair;
 
struct edge {
  int to;
  int cap;
  int rev;
  double cost;
};
 
int V;
vector<edge> G[MAX_V];
double h[MAX_V];
double dist[MAX_V];
int prevv[MAX_V],preve[MAX_V];
 
void init_edge(){
  for(int i=0;i<MAX_V;i++)G[i].clear();
}
 
void add_edge(int from,int to,int cap,double cost){
  G[from].push_back((edge){to,cap,(int)G[to].size(),cost});
  G[to].push_back((edge){from,0,(int)G[from].size()-1,-cost});
}
 
double min_cost_flow(int s,int t,int f){
  double eps = 1e-5;
  double res = 0;
  fill(h,h+V,0.0);
   
  while(f>0){
     
    priority_queue< Pair, vector<Pair>, greater<Pair> >  que;
    fill( dist, dist+V , (double)INF );
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

double getCost(P a,P b,C c,C d,bool debug=false){
  
  if( getState(c,S(a,b)) == 1 && getState(d,S(a,b)) == 1 ){
    return abs(a-b);
  }
  
  vector< S > va,vb,tmp;
  getTangent(c,a,va);
  getTangent(d,a,va);
  getTangent(c,b,vb);
  getTangent(d,b,vb);


  double res=1e20;
  
  for(int i=0;i<(int)va.size();i++){
    for(int j=0;j<(int)vb.size();j++){
      S as=va[i];
      S bs=vb[j];
      if( isParallel(as,bs) )continue;
      P target=getcrosspoint(as.p, as.q, bs.p, bs.q);
      
      if( getState(c, S(a,target)) !=1 )continue;
      if( getState(c, S(b,target)) !=1 )continue;
      if( getState(d, S(a,target)) !=1 )continue;
      if( getState(d, S(b,target)) !=1 )continue;
      /*
      if(debug){
        
        cout<<as.p<<' '<<as.q<<' '<<bs.p<<' '<<bs.q<<endl;
        
      }
      */
      res=min(res, abs(target-a)+abs(target-b) );
    }
  }

  return res;
}

int n;
int SI,TI;
P a[105],b[105];


int main(){
  cin>>n;
  
  double x,y,r;
  cin>>x>>y>>r;
  C ca(x,y,r- (1e-8));
  
  cin>>x>>y>>r;
  C cb(x,y,r- (1e-8));
  

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
      double cost=getCost(a[i],b[j],ca,cb, i==0&&j==0);
      
      add_edge(i,n+j,1,cost);
    }
  }


  double ans=min_cost_flow(SI,TI,n);
  if(ans<0){
    cout<<"Impossible"<<endl;
  }else{
    printf("%.10f\n",ans);
  }
  return 0;
}
