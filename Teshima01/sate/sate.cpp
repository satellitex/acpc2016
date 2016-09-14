#include<bits/stdc++.h>
using namespace std;
typedef complex<double> P;

typedef pair<P,P> L;

const double EPS = 1e-8;
const double INF = 1e100;

double dot(P a, P b){ return a.real() * b.real() + a.imag() * b.imag(); }
double cross(P a, P b){ return   a.real() * b.imag() - a.imag() * b.real(); }

// 線分と点の交差判定
bool isIntersectSP(L s, P p){ 
  return abs(s.first-p) + abs(s.second-p) - abs(s.second-s.first) < EPS; 
}
// ２直線間の交点
P crossPoint(L l, L m){
  double A = cross(l.second - l.first, m.second - m.first);
  double B = cross(l.second - l.first, l.second - m.first);
  if(fabs(A) < EPS && fabs(B) < EPS) return m.first;
  else if(fabs(A) >= EPS) return m.first + B / A * (m.second - m.first);
  else return P(INF,INF);
}
//円
struct Circle{
  P c; //中心点
  double r; //半径
  Circle(P c=P(0,0), double r=0):c(c),r(r){}
};

P rotate(P p, double theta){
  theta = theta * M_PI / 180.0;
  double x = real(p) * cos(theta) - imag(p) * sin(theta);
  double y = real(p) * sin(theta) + imag(p) * cos(theta);
  return P(x,y);
}

//射影
P proj(P p, L l){
  return l.first + dot(p - l.first, l.second - l.first) / norm(l.second - l.first) * (l.second - l.first);
}

//円と線分の交点
vector<P> getIntersectCS(Circle c, L s){
  vector<P> res;
  P h = proj(c.c, s);
  double d = abs(c.c - h);

  if( abs( s.first - c.c ) - c.r < -EPS ||
      abs( s.second - c.c ) -c.r < -EPS ) {
    res.push_back( P(INF,INF) );
    res.push_back( P(INF,INF) );
    return res;
  }
  if(d > c.r + EPS);
  else if(d > c.r - EPS){
    if(isIntersectSP(s,h)) res.push_back(h);
  }
  else {
    P v = s.second - s.first;
    v = (sqrt(c.r*c.r - d*d) / abs(v)) * v;
    if(isIntersectSP(s, h+v)) res.push_back(h+v);
    if(isIntersectSP(s, h-v)) res.push_back(h-v);
  }
  return res;
}

//点から円に引いた接線の交点
vector<P> tangent(Circle c, P p){
  vector<P> res;
  double a = abs(p - c.c);
  if(a < c.r - EPS);
  else if(a < c.r + EPS) {
    res.push_back( p + rotate( c.c - p, 90.0 ) );
    res.push_back( p + rotate( c.c - p, -90.0 ) );
  }
  else {
    double b = sqrt(a*a-c.r*c.r);
    double psi = arg(p - c.c);
    double phi = M_PI - acos(b/a);
    res.push_back(p + b * P(cos(psi+phi), sin(psi+phi)));
    res.push_back(p + b * P(cos(psi-phi), sin(psi-phi)));
  }
  return res;
}


typedef pair<double,int> Pa;
const int MAX_V = 1000;

struct edge{
  int to, cap;
  double cost;
  int rev;
};

int V;
vector<edge> G[MAX_V];
double h[MAX_V];
double dist[MAX_V];
int prevv[MAX_V],preve[MAX_V];
 
void init(){
  for(int i = 0 ; i < MAX_V ; i++){
    G[i].clear();
  }
}
 
void add_edge(int from,int to,int cap,double cost){
  G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
  G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
}

double min_cost_flow(int s,int t,int f){
  double res = 0;
  fill(h,h+V,0.0);
  while(f > 0){
    priority_queue<Pa,vector<Pa>,greater<Pa> > que;
    fill(dist,dist + V,INF);
    dist[s] = 0;
    que.push(Pa(0,s));
    while(!que.empty()){
      Pa p = que.top(); que.pop();
      int v = p.second;
      
      if(dist[v] < p.first)continue;
      for(int i = 0 ; i < (int)G[v].size() ; i++){
        edge &e = G[v][i];
         
        if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to] + EPS ){
          dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
          prevv[e.to] = v;
          preve[e.to] = i;
          que.push(Pa(dist[e.to],e.to));
        }
      }
    }
 
    if(dist[t] > INF / 2.0){
      return -1;
    }
 
    for(int v = 0 ; v < V ; v++) h[v] += dist[v];
       
    int d = f;
    
    for(int v = t; v != s; v = prevv[v]){
      d = min(d,G[prevv[v]][preve[v]].cap);
    }
    f -= d;
    res += d * h[t];
    for(int v = t ; v != s ; v = prevv[v]){
      edge &e = G[prevv[v]][preve[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}


int N;
vector<Circle> cs;
vector<P> bs,rs;
bool isTouchCircle( L s ){
  for( Circle c : cs )
    if( getIntersectCS( c, s ).size()==2 )
      return true;  
  return false;
}
double solve(){
  V = 2*N + 2;
  int S = 2*N, T = 2*N+1;
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      L s = L( bs[i], rs[j] );
      double cost = INF;
      if( !isTouchCircle( s ) ) 
        cost = abs( s.first - s.second );      
      vector<P> vb, vr;
      for( Circle c : cs ){
        vector<P> v = tangent( c, bs[i] );
        vb.insert( vb.end(), v.begin(), v.end() );
        v = tangent( c, rs[j] );
        vr.insert( vr.end(), v.begin(), v.end() );
      }
      for( P pb : vb ){
        for( P pr : vr ){
          if( abs( bs[i] - rs[j] ) - abs( bs[i] - pb ) - abs( rs[j] - pb ) > -EPS ) continue;
          if( abs( bs[i] - rs[j] ) - abs( bs[i] - pr ) - abs( rs[j] - pr ) > -EPS ) continue;
          P xp = crossPoint( L( pb, bs[i] ), L( pr, rs[j] ) );
          if( xp.real() > INF/2.0 ) continue;
          L sb = L( xp, bs[i] ), sr = L( xp, rs[j] );
          if( !isTouchCircle( sb ) && !isTouchCircle( sr ) )
            cost = min( cost, abs( bs[i] - xp ) + abs( rs[j] - xp ) );
        }
      }
      if( cost < INF/2.0 )
        add_edge( i, N+j, 1, cost );
    }    
    add_edge( S, i, 1, 0.0 );
    add_edge( N+i, T, 1, 0.0 );
  }
  return min_cost_flow( S, T, N );
}

int main(){
  cin >> N;
  cs.resize(2);
  for(int i=0;i<2;i++){
    int x,y,r; cin >> x >> y >> r;
    cs[i] = Circle( P(x, y), r );    
  }
  bs.resize(N);
  rs.resize(N);
  for(int i=0;i<N;i++){
    int x,y; cin >> x >> y; bs[i] = P( x, y );
  }
  for(int i=0;i<N;i++){
    int x,y; cin >> x >> y; rs[i] = P( x, y );
  }
  double res = solve();
  if( res < -0.5 ) cout << "Impossible" << endl;
  else  printf("%.10lf\n", res );
}

