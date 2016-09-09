#include <bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i=a;i<(int)b;i++)
#define rep(i,n) REP(i,0,n)
#define all(c) (c).begin(), (c).end()
#define zero(a) memset(a, 0, sizeof a)
#define minus(a) memset(a, -1, sizeof a)
#define watch(a) { cout << #a << " = " << a << endl; }
template<class T1, class T2> inline bool minimize(T1 &a, T2 b) { return b < a && (a = b, 1); }
template<class T1, class T2> inline bool maximize(T1 &a, T2 b) { return a < b && (a = b, 1); }

typedef long long ll;
int const inf = 1<<29;

namespace point_2d {

using Real = double;

Real const EPS = 1e-7;  // !!! DO CHECK EPS !!!

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

bool intersect_gs(Polygon const& g, Segment const& s) { // not verified
  auto u = const_cast<Polygon&>(g);
  rep(i, g.size()) {
    if(!intersect_sp(s, u[i]) && intersect_ss(s, u.side(i))) { return true; }
  }
  return false;
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

// 通常clangであれば、"(x, y)"の形式を読み取るが、これを"x y"に変更する
istream& operator >> (istream& is, P& p) { Real x, y; is >> x >> y; p = P(x, y); return is; }
ostream& operator << (ostream& os, Line const& l) { return os << "{" << l[0] << ", " << l[1] << "}"; }

}
using namespace point_2d;

struct xor128 {
  unsigned x,y,z,w;
  xor128(): x(89165727), y(157892372), z(7777777), w(757328) {}
  unsigned next() {
    unsigned t=x^(x<<11);
    x=y;y=z;z=w;
    return w=w^(w>>19)^t^(t>>8);
  }
  unsigned next(unsigned k) {
    return next()%k;
  }
} rndgen;

namespace visualizer {

ofstream ofs;

P offset = P(0, 0);
int zoom = 1;

void init() {
  ofs = ofstream("data.js");
}

string random_color() {
  stringstream ss; ss << std::hex << rndgen.next(16777216);
  return "#" + ss.str();
}

ostream& line(Line l, bool use_random_color = true) {
  l[0] += offset, l[1] += offset;
  l[0] *= zoom, l[1] *= zoom;
  return ofs << "line(" << l[0].real() << "," << l[0].imag() << ","
    << l[1].real() << "," << l[1].imag() << ","
    << (use_random_color ? "\"" + random_color() + "\"" : "\"#000000\"") << ")"
    << endl;
}

ostream& circle(Circle c, string color = "") {
  c.p += offset;
  c = Circle(P(c.p.real() * zoom, c.p.imag() * zoom), c.r * zoom);
  return ofs << "circle(" << c.p.real() << "," << c.p.imag() << "," << c.r << ","
  << (color.empty() ? "\"" + random_color() + "\"" : "\"" + color + "\"") << ")" << endl;
}

ostream& plot(P p, string color = "") {
  p += offset;
  auto c = Circle(P(p.real() * zoom, p.imag() * zoom), 0.1 * zoom);
  return ofs << "circle(" << c.p.real() << "," << c.p.imag() << "," << c.r << ","
  << (color.empty() ? "\"" + random_color() + "\"" : "\"" + color + "\"") << ")" << endl;
}

void show_picture() {
  ofs.close();
  int r = system("open visualizer.html");
  assert(!WEXITSTATUS(r));
}

}

int main() {

  int N; cin >> N;
  Circle cs[2]; rep(i, 2) cin >> cs[i].p >> cs[i].r;
  P rp[100];    rep(i, N) cin >> rp[i];
  P bp[100];    rep(i, N) cin >> bp[i];

  {
    using namespace visualizer;
    init();
    offset = P(100, 100);
    zoom = 3;
    circle(cs[0], "#ff0000");
    circle(cs[1], "#0000ff");
    rep(i, N) plot(rp[i], "#ff0000"), plot(bp[i], "#0000ff");
    show_picture();
  }

  return 0;
}