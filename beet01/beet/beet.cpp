#include<bits/stdc++.h>
using namespace std;
#define EPS (1e-10)
#define equals(a,b) (fabs((a)-(b)) < EPS)

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

double cross(Vector a,Vector b){
  return a.x*b.y-a.y*b.x;
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

int main(){
  int n,k;
  cin >> n >> k;
  Polygon v,c;
  int i;
  int d[4]={0,k,1,1-k};
  for(i=0;i<4;i++){
    double x=2*PI/n*d[i];
    v.push_back(Point(cos(x),sin(x)));
  }
  c.push_back(getCrossPoint(v[0],v[1],v[2],v[3]));
  printf("%.8lf\n",cross(v[0],c[0])*n);
  return 0;
}
