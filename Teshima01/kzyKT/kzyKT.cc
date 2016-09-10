#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-10,INF = 1e12;
typedef complex<double> P;
typedef pair<P,P> L;
struct C{P p;double r;};
namespace std {
  bool operator < (const P& a, const P& b) {
    return real(a)!=real(b)?real(a)<real(b):imag(a)<imag(b);
  }
}
double cross(const P& a, const P& b) {return imag(conj(a)*b);}
double dot(const P& a, const P& b) {return real(conj(a)*b);}
P proj(P p, L l){
  return l.first + dot(p - l.first, l.second - l.first) / norm(l.second - l.first) * (l.second - l.first);
}
double D(P a, P b) {
  return sqrt((a.real()-b.real())*(a.real()-b.real())+(a.imag()-b.imag())*(a.imag()-b.imag()));
}
bool intersectSP(const L &s, const P &p) {return abs(s.first-p)+abs(s.second-p)-abs(s.second-s.first) < EPS;}
bool intersectLL(const L &l, const L &m) {
  return abs(cross(l.second-l.first, m.second-m.first)) > EPS ||
         abs(cross(l.second-l.first, m.first-l.first)) < EPS;
}
P crosspoint(const L &l, const L &m) {
  double A = cross(l.second - l.first, m.second - m.first);
  double B = cross(l.second - l.first, l.second - m.first);
  if (fabs(A) < EPS && fabs(B) < EPS) return m.first;
  if (fabs(A) < EPS) assert(false);
  return m.first + B / A * (m.second - m.first);
}
vector<P> getIntersectCS(C c, L s){
  vector<P> res;
  P h = proj(c.p, s);
  double d = abs(c.p - h);
  if(d > c.r + EPS);
  else if(d > c.r - EPS){
    if(intersectSP(s,h)) res.push_back(h);
  }
  else {
    P v = s.second - s.first;
    v = (sqrt(c.r*c.r - d*d) / abs(v)) * v;
    if(intersectSP(s,h+v)) res.push_back(h+v);
    if(intersectSP(s,h-v)) res.push_back(h-v);
  }
  return res;
}
double toRad(double agl) {return agl*M_PI/180.0;}
P rotate(P a, double r){return P(a.real()*cos(r)-a.imag()*sin(r),a.real()*sin(r)+a.imag()*cos(r));}
vector<P> tangent(C c, P q){
  vector<P> res;
  double a = abs(q - c.p);
  if(a < c.r - EPS);
  else if(a < c.r + EPS) res.push_back(rotate(c.p-q,toRad(90))+q);
  else {
    double b = sqrt(a*a-c.r*c.r);
    double psi = arg(q - c.p);
    double phi = M_PI - acos(b/a);
    res.push_back(q + b * P(cos(psi+phi), sin(psi+phi)));
    res.push_back(q + b * P(cos(psi-phi), sin(psi-phi)));
  }
  return res;
}
const int MAX_V= 1002;
struct edge{
  int to,cap,rev;
  double cost;
  edge(int to,int cap,double cost,int rev) :to(to),cap(cap),cost(cost),rev(rev) {}
};
vector<edge> G[MAX_V];
double dist[MAX_V];
int prevv[MAX_V],preve[MAX_V];
void add_edge(int from,int to,int cap,double cost){
  G[from].push_back(edge(to,cap,cost,G[to].size()));
  G[to].push_back(edge(from,0,-cost,G[from].size()-1));
}
double min_cost_flow(int s,int t,int f){
  double res=0;
  while(f>0){
    fill(dist,dist+MAX_V,INF);dist[s]=0;
    bool update=true;
    while(update){
      update=false;
      for(int v=0;v<MAX_V;v++){
        if(dist[v]==INF) continue;
        for(int i=0;i<(int)G[v].size();i++){
          edge &e=G[v][i];
          if(e.cap>0 && dist[e.to]>dist[v]+e.cost+EPS){
            dist[e.to]=dist[v]+e.cost;
            prevv[e.to]=v; preve[e.to]=i; update=true;
          }
        }
      }
    }
    if(dist[t]==INF)return -1;
    int d=f;
    for(int v=t;v!=s;v=prevv[v]){
      d=min(d,G[prevv[v]][preve[v]].cap);
    }
    f-=d;res+=dist[t]*d;
    for(int v=t;v!=s;v=prevv[v]){
      edge &e=G[prevv[v]][preve[v]];
      e.cap-=d;G[v][e.rev].cap+=d;
    }
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  C c[2];
  for(int i=0,x,y,z; i<2; i++) {
    cin >> x >> y >> z;
    c[i]=(C){P(x,y),(double)z};
  }
  vector<P> a(n),b(n);
  vector<vector<L>> v(n),v2(n);
  for(int i=0,x,y; i<n; i++) {
    cin >> x >> y;
    a[i]=P(x,y);
    for(int j=0; j<2; j++) {
      vector<P> g=tangent(c[j],a[i]);
      for(int k=0; k<g.size(); k++) v[i].push_back(L(a[i],g[k]));
    }
  }
  for(int i=0,x,y; i<n; i++) {
    cin >> x >> y;
    b[i]=P(x,y);
    for(int j=0; j<2; j++) {
      vector<P> g=tangent(c[j],b[i]);
      for(int k=0; k<g.size(); k++) v2[i].push_back(L(b[i],g[k]));
    }
  }
  double d[n][n];
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      d[i][j]=INF;
      for(int k=0; k<v[i].size(); k++) {
        for(int l=0; l<v2[j].size(); l++) {
          if(!intersectLL(v[i][k],v2[j][l])) continue;
          P p=crosspoint(v[i][k],v2[j][l]);
          bool f=1;
          for(int x=0; x<2; x++) {
            if(D(p,c[x].p)<c[x].r) f=0;
            if(getIntersectCS(c[x],L(a[i],p)).size()>=2) f=0;
            if(getIntersectCS(c[x],L(b[j],p)).size()>=2) f=0;
          }
          if(f) d[i][j]=min(d[i][j],D(a[i],p)+D(b[j],p));
        }
      }
      bool f=1;
      for(int x=0; x<2; x++) {
        if(getIntersectCS(c[x],L(a[i],b[j])).size()>=2) f=0;
      }
      if(f) d[i][j]=min(d[i][j],D(a[i],b[j]));
      if(d[i][j]!=INF) add_edge(i,n+j,1,d[i][j]);
    }
    add_edge(1000,i,1,0);
    add_edge(i+n,1001,1,0);
  }
  double ans=min_cost_flow(1000,1001,n);
  if(ans<0) printf("-1\n");
  else printf("%.10f\n",ans);
  return 0;
}
