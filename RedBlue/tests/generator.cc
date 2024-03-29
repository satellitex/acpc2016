#include <bits/stdc++.h>
#include "testlib.h"

#define REP(i,a,b) for(int i=a;i<(int)b;i++)
#define rep(i,n) REP(i,0,n)

using namespace std;

namespace point_2d {

using Real = double;

Real const EPS = 1e-8;  // !!! DO CHECK EPS !!!

typedef complex<Real> P;

bool operator < (P const& l, P const& r) {
  return abs(l.real() - r.real()) < EPS ? l.imag() < r.imag() : l.real() < r.real();
}

bool operator > (P const& l, P const& r) {
  return abs(l.real() - r.real()) < EPS ? l.imag() > r.imag() : l.real() > r.real();
}

bool equals(Real a, Real b) {
  return abs(a - b) < EPS;
}

bool equals (P const& l, P const& r) {
  return abs(l - r) < EPS;
}

struct Line : public pair<P, P> {
  Line(P const& a, P const& b) { first = a, second = b; }
  const P& operator[] (int x) const { return x == 0 ? first : second; }
  P& operator[] (int x) { return x == 0 ? first : second; }
};
typedef Line Segment;

struct Circle {
  P p; Real r;
  Circle(){}
  Circle(P const& p, Real r): r(r) { this->p = p; }
};

struct Polygon : public vector<P> {
  vector<P>& g = *this;
  Polygon() = default;
  Polygon(vector<P> const& g) { this->g = g; }
  P& operator[] (int x) { return vector<P>::operator[]((x + size()) % size()); }
  Segment side(int x) { return std::move(Segment(this->operator[](x), this->operator[](x+1))); }
  Segment backside(int x) { return std::move(Segment(this->operator[](x), this->operator[](x-1))); }
};

Real cross(P const& a, P const& b) { return imag(conj(a)*b); }
Real dot(P const& a, P const& b) { return real(conj(a)*b); }
Real cos(P const& l, P const& r) { return dot(l, r) / (abs(l) * abs(r)); }  // not verified

enum ccw_result {
  counter_clockwise = +1, clockwise = -1, online_back = +2, online_front = -2, on_segment = 0
};

ccw_result ccw(P a, P b, P c) {
  b -= a, c -= a;
  if(cross(b, c) > 0)   { return ccw_result::counter_clockwise; }
  if(cross(b, c) < 0)   { return ccw_result::clockwise; }
  if(dot(b, c) < 0)     { return ccw_result::online_back; }
  if(norm(b) < norm(c)) { return ccw_result::online_front; }
  return ccw_result::on_segment;
}

bool intersect_lp(Line const& l, P const& p) {
  return abs(cross(l[1]-p, l[0]-p)) < EPS;
}

bool intersect_sp(Line const& s, P const& p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}

bool intersect_ss(Segment const& s, Segment const& t) {
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= EPS &&
         ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= EPS;
}

bool intersect_ll(Line const& l, Line const& m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
         abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}

bool intersect_ls(Line const& l, Segment const& s) {
  return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
         cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}

P projection(Line const& l, P const& p) {
  auto t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
}

P reflection(Line const& l, P const& p) {
  return p + (Real)2.0 * (projection(l, p) - p);
}

Real distance_sp(Line const& s, P const& p) {
  P const r = projection(s, p);
  if(intersect_sp(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}

Real distance_lp(Line const& l, P const& p) {
  return abs(p - projection(l, p));
}

bool intersect_cl(Circle const& c, Line const& l) {
  return distance_lp(l, c.p) <= c.r + EPS;
}

bool intersect_cs(Circle const& c, Line const& l) {
  if(abs(l[0] - c.p) < c.r - EPS && abs(l[1] - c.p) < c.r - EPS) { return false; }
  return distance_lp(l, c.p) <= c.r + EPS;
}

bool intersect_cc(Circle const& c1, Circle const& c2) {
  return abs(c1.p - c2.p) <= c1.r + c2.r + 1e-3;
}

bool intersect_gs(Polygon const& g, Segment const& s) { // not verified
  auto u = const_cast<Polygon&>(g);
  rep(i, g.size()) {
    if(!intersect_sp(s, u[i]) && intersect_ss(s, u.side(i))) { return true; }
  }
  return false;
}

bool contains_cp(Circle const& c, P const& p) {
    return abs(c.p - p) <= c.r + 1e-3;
}

P crosspoint(const Line &l, const Line &m) {
  auto A = cross(l[1] - l[0], m[1] - m[0]);
  auto B = cross(l[1] - l[0], l[1] - m[0]);
  if(abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if(abs(A) < EPS) assert(false && "PRECONDITION NOT SATISFIED");
  return m[0] + B / A * (m[1] - m[0]);
}

pair<P, P> crosspoint(Circle const& c, Line const& l) {
  auto h = projection(l, c.p);
  auto e = (l[1]-l[0]) / abs(l[1]-l[0]);
  auto base = sqrt(c.r*c.r-abs(h-c.p)*abs(h-c.p));
  return {h+e*base, h-e*base};
}

pair<P, P> crosspoint(Circle c1, Circle c2) {
  if(c1.p.real() > c2.p.real()) swap(c1, c2);
  auto const d = abs(c2.p - c1.p);
  auto const alpha  = acos((c2.p.real() - c1.p.real()) / d) * ((c1.p.imag() > c2.p.imag()) ? -1.0 : 1.0);
  auto const beta   = acos((c1.r * c1.r - c2.r * c2.r + d * d) / 2.0 / d / c1.r);
  return make_pair(c1.p + polar(c1.r, alpha - beta), c1.p + polar(c1.r, alpha + beta));
}
 
vector<P> tangent_points(Circle const& c, P const& p) {
  vector<P> ret;
  auto const sec2 = norm(p - c.p);
  auto const tan2 = max(Real(0), sec2 - c.r * c.r);
  auto const nv = (p - c.p) * c.r * c.r / sec2;
  auto const pv = (p - c.p) * P(0, -1) * c.r * sqrt(tan2) / sec2;
  ret.push_back(c.p + nv + pv);
  ret.push_back(c.p + nv - pv);
  return ret;
}

istream& operator >> (istream& is, P& p) { Real x, y; is >> x >> y; p = P(x, y); return is; }

}
using namespace point_2d;

const int N_MIN =   1;
const int N_MAX = 100;

const int X_MIN = -1000;
const int X_MAX = +1000;
const int Y_MIN = -1000;
const int Y_MAX = +1000;
const int R_MIN =     1;
const int R_MAX =    50;

const int RX_MIN = -1000;
const int RX_MAX = +1000;
const int RY_MIN = -1000;
const int RY_MAX = +1000;

const int BX_MIN = -1000;
const int BX_MAX = +1000;
const int BY_MIN = -1000;
const int BY_MAX = +1000;

int n;
int X1, Y1, R1;
int X2, Y2, R2;
int rx[N_MAX], ry[N_MAX];
int bx[N_MAX], by[N_MAX];

bool validate()
{

    Circle rc(P(X1, Y1), R1);
    Circle bc(P(X2, Y2), R2);

    if(intersect_cc(rc, bc))
        return false;

    rep(i, n) {
        auto rp = P(rx[i], ry[i]);
        auto bp = P(bx[i], by[i]);
        if(contains_cp(rc, rp) || contains_cp(bc, rp))
            return false;
        if(contains_cp(rc, bp) || contains_cp(bc, bp))
            return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    for (int t = 0; t < 30; t++) {
        ofstream of(format("2_random_%02d.in", t));
        n = rnd.next(N_MIN, N_MAX);
        
        X1 = rnd.next(X_MIN, X_MAX);
        Y1 = rnd.next(Y_MIN, Y_MAX);
        R1 = rnd.next(R_MIN, R_MAX);
        
        X2 = rnd.next(X_MIN, X_MAX);
        Y2 = rnd.next(Y_MIN, Y_MAX);
        R2 = rnd.next(R_MIN, R_MAX);
        
        for (int i = 0; i < n; i++) {
            rx[i] = rnd.next(RX_MIN, RX_MAX);
            ry[i] = rnd.next(RY_MIN, RY_MAX);
        }
        
        for (int i = 0; i < n; i++) {
            bx[i] = rnd.next(BX_MIN, BX_MAX);
            by[i] = rnd.next(BY_MIN, BY_MAX);
        }

        if(validate()) {
            of << n << endl;
            of << X1 << " " << Y1 << " " << R1 << endl;
            of << X2 << " " << Y2 << " " << R2 << endl;
            for(int i=0; i<n; i++) {
                of << rx[i] << " " << ry[i] << endl;
            }
            for(int i=0; i<n; i++) {
                of << bx[i] << " " << by[i] << endl;
            }
        }
        else {
            t --;
        }
    }
    return 0;
}
