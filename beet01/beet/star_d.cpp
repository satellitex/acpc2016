#include<bits/stdc++.h>
using namespace std;
#define EPS (1e-10)
#define equals(a,b) (fabs((a)-(b)) < EPS)
 
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

static const double PI = 3.14159265358979;
 
struct Point{
  double x,y;
  Point(){}
  Point(double x,double y):x(x),y(y){}
  
  Point operator+(Point p){return Point(x+p.x,y+p.y);}
  Point operator-(Point p){return Point(x-p.x,y-p.y);}
  Point operator*(double k){return Point(x*k,y*k);}
  Point operator/(double k){return Point(x/k,y/k);}
   
  double norm(){return x*x+y*y;}
  double abs(){return sqrt(norm());}
 
  bool operator<(const Point &p) const{
    return x!=p.x? x< p.x : y < p.y;
  }
 
  bool operator==(const Point &p) const{
    return fabs(x-p.x) < EPS && fabs(y-p.y) < EPS ;
  }
};
 
typedef Point Vector;
 
struct Segment{
  Point p1,p2;
  Segment(Point p1,Point p2):p1(p1),p2(p2){}
};

typedef Segment Line;

double dot(Vector a,Vector b){
  return a.x*b.x+a.y*b.y;
}
double cross(Vector a,Vector b){
  return a.x*b.y-a.y*b.x;
}
int ccw(Point p0,Point p1,Point p2){
  Vector a = p1-p0;
  Vector b = p2-p0;
  if(cross(a,b) > EPS) return COUNTER_CLOCKWISE;
  if(cross(a,b) < -EPS) return CLOCKWISE;
  if(dot(a,b) < -EPS) return ONLINE_BACK;
  if(a.norm()<b.norm()) return ONLINE_FRONT;
  return ON_SEGMENT;
}
typedef vector<Point> Polygon;


Point getCrossPoint(Segment s1,Segment s2){
  Vector base = s2.p2 - s2.p1;
  double d1 = fabs(cross(base,s1.p1-s2.p1));
  double d2 = fabs(cross(base,s1.p2-s2.p1));
  double t = d1 / (d1+d2);
  return s1.p1 + (s1.p2 - s1.p1) * t;
}

Point getCrossPoint(Point p0,Point p1,Point p2,Point p3){
  return getCrossPoint(Segment(p0,p1),Segment(p2,p3));
}

double area(Polygon p){
  double x=0;
  for(int i=0;i<p.size();i++){
    x+=cross(p[i],p[(i+1)%p.size()])/2.0;
  }
  return x;
}
int main(){
  int n,k;
  cin >> n >> k;
  Polygon v,c,p;
  int i;
  for(i=0;i<n;i++){
    double x=2*PI/n*i;
    v.push_back(Point(cos(x),sin(x)));
  }
  //for(i=0;i<n;i++) cout << "set label "<<(i+1)<<" point pt 7 ps 1 at " << v[i].x << "," << v[i].y << endl;
  //for(i=0;i<=n;i++) cout << v[(i*2)%n].x << " " << v[(i*2)%n].y << endl;
  for(i=0;i<n;i++){
    c.push_back(getCrossPoint(v[(i+n)%n],v[(i+n+k)%n],v[(i+n+1)%n],v[(i+n+1-k)%n]));
  }
  for(i=0;i<n;i++){
    p.push_back(v[i]);
    p.push_back(c[i]);
  }
  
  for(i=0;i<2*n+1;i++) cout << p[i%(2*n)].x << " " << p[i%(2*n)].y << endl;
  
  //  cout << area(p) << endl;
  return 0;
}
