#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#define f first
#define s second
#define mp make_pair
#define pi M_PI
#define inf 1e15
#define eps (1e-6)
#define equals(a,b) (fabs((a)-(b))<eps)
#define MAX 300
using namespace std;

typedef pair<double,int> P;

class Point{
public:
  double x,y;
  Point(double x=0,double y=0):x(x),y(y){}

  Point operator+(Point p){ return Point(x+p.x,y+p.y);}
  Point operator-(Point p){ return Point(x-p.x,y-p.y);}
  Point operator*(double k){ return Point(x*k,y*k);}
  Point operator/(double k){ return Point(x/k,y/k);}
  bool operator<(Point p)const{ return (x!=p.x ? x<p.x : y<p.y);}
  bool operator==(Point p)const{ return fabs(x-p.x)<eps && fabs(y-p.y)<eps;}

  double abs(){ return sqrt(norm());}
  double norm(){ return (x*x+y*y);}
};
typedef Point Vector;
typedef vector<Point> Polygon;

class Segment{
public:
  Point p1,p2;
  Segment(Point p1=Point(),Point p2=Point()):p1(p1),p2(p2){}
};
typedef Segment Line;

class Circle{
public:
  Point c;
  double r;
  Circle(Point c=Point(),double r=0.0):c(c),r(r){}
};

double norm(Vector a){ return (a.x*a.x+a.y*a.y);}
double abs(Vector a){ return sqrt(norm(a));}
double dot(Vector a,Vector b){ return (a.x*b.x+a.y*b.y);}
double cross(Vector a,Vector b){ return (a.x*b.y-a.y*b.x);}

bool isParallel(Segment a,Segment b){
  return equals(cross(a.p1-a.p2,b.p1-b.p2),0.0);
}

Point getCrossPointLL(Line a,Line b){
  double A=cross(a.p2-a.p1,b.p2-b.p1);
  double B=cross(a.p2-a.p1,a.p2-b.p1);
  if(abs(A)<eps || abs(B)<eps)return b.p1;
  return b.p1+(b.p2-b.p1)*(B/A);
}

Point rotate(Point base,Point a,double r){
  Point b=a-base;
  a.x=b.x*cos((r/180)*M_PI)-b.y*sin((r/180)*M_PI);
  a.y=b.x*sin((r/180)*M_PI)+b.y*cos((r/180)*M_PI);
  a=a+base;
  return a;
}

pair<Point,Point> getTangent(Circle c,Point p){
  Vector v=p-c.c;
  if(equals(abs(c.c-p),c.r))return mp(rotate(p,c.c,90),rotate(p,c.c,270));
  double r=acos(c.r/abs(v))*360/(2*pi);
  v=v*c.r/abs(v);
  Point p1=rotate(c.c,c.c+v,r);
  Point p2=rotate(c.c,c.c+v,360-r);
  return mp(p1,p2);
}

double getDistanceLP(Line l,Point p){
  return abs(cross(l.p2-l.p1,p-l.p1)/abs(l.p2-l.p1));
}

double getDistanceSP(Segment s,Point p){
  if(dot(s.p2-s.p1,p-s.p1)<0.0)return abs(p-s.p1);
  if(dot(s.p1-s.p2,p-s.p2)<0.0)return abs(p-s.p2);
  return getDistanceLP(s,p);
}

bool intersect(Circle c,Segment s){
  if(getDistanceSP(s,c.c)-c.r<-eps)return true;
  return false;
}

int n;
Circle R,B;
vector<Point> r,b;

vector<Line> getS(Point p){
  vector<Line> res;
  pair<Point,Point> pp=getTangent(R,p);
  res.push_back(Line(p,pp.f));
  res.push_back(Line(p,pp.s));
  pp=getTangent(B,p);  
  res.push_back(Line(p,pp.f));
  res.push_back(Line(p,pp.s));
  return res;
}

double getdis(int c,int d){
  Segment s(r[c],b[d]);
  if(!intersect(R,s) && !intersect(B,s))return abs(r[c]-b[d]);
  vector<Line> vs1=getS(r[c]),vs2=getS(b[d]);
  double res=inf;
  for(int i=0;i<vs1.size();i++){
    for(int j=0;j<vs2.size();j++){
      if(isParallel(vs1[i],vs2[j]))continue;
      Point m=getCrossPointLL(vs1[i],vs2[j]);
      if(!intersect(R,Segment(r[c],m)) && !intersect(B,Segment(m,b[d])) &&
         !intersect(B,Segment(r[c],m)) && !intersect(R,Segment(m,b[d])))
        res=min(res,abs(r[c]-m)+abs(m-b[d]));
    }
  }
  return res;
}

struct edge{ 
  int to,cap;
  double cost;
  int rev;
};

int v;
vector<edge> e[MAX];
double h[MAX];
double dist[MAX];
int prevv[MAX],preve[MAX];

void add_edge(int from,int to,int cap,double cost){
  e[from].push_back((edge){to,cap,cost,(int)e[to].size()});
  e[to].push_back((edge){from,0,-cost,(int)e[from].size()-1});
}

double min_cost_flow(int s,int t,int f){
  double res=0.0;
  fill(h,h+v,0);
  while(f>0){
    priority_queue<P,vector<P>,greater<P> > pq;
    fill(dist,dist+v,inf);
    dist[s]=0;
    pq.push(P(0,s));
    while(pq.size()){
      P p=pq.top();
      pq.pop();
      int u=p.second;
      if(dist[u]-p.first<-eps)continue;
      for(int i=0;i<e[u].size();i++){
        edge &E=e[u][i];
        if(E.cap>0 && (dist[u]+E.cost+h[u]-h[E.to])-dist[E.to]<-eps){
          dist[E.to]=dist[u]+E.cost+h[u]-h[E.to];
          prevv[E.to]=u;
          preve[E.to]=i;
          pq.push(P(dist[E.to],E.to));
        }
      }
    }
    if(dist[t]==inf)return -1;
    for(int i=0;i<v;i++)h[i]+=dist[i];

    int d=f;
    for(int u=t;u!=s;u=prevv[u]){
      d=min(d,e[prevv[u]][preve[u]].cap);
    }
    f-=d;
    res+=(double)d*h[t];
    for(int u=t;u!=s;u=prevv[u]){
      edge &E=e[prevv[u]][preve[u]];
      E.cap-=d;
      e[u][E.rev].cap+=d;
    }
  }
  return res;
}

int main()
{
  cin>>n;
  cin>>R.c.x>>R.c.y>>R.r;
  cin>>B.c.x>>B.c.y>>B.r;
  for(int i=0;i<n;i++){
    int x,y;
    cin>>x>>y;
    r.push_back(Point(x,y));
  }
  for(int i=0;i<n;i++){
    int x,y;
    cin>>x>>y;
    b.push_back(Point(x,y));
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      double d=getdis(i,j);
      if(d!=inf)add_edge(i,j+n,1,d);
     }
  }
  int s=n*2;
  int t=s+1;
  v=t+1;
  for(int i=0;i<n;i++){
    add_edge(s,i,1,0);
    add_edge(i+n,t,1,0);
  }
  double res=min_cost_flow(s,t,n);
  if(res==-1)cout<<"Impossible"<<endl;
  else printf("%.10f\n",res);
  return 0;
}
