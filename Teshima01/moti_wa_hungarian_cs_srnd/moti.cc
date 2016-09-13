#include <bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i=a;i<(int)b;i++)
#define rep(i,n) REP(i,0,n)

int const inf = 1<<29;

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

struct Line : public pair<P, P> {
  Line() = default;
  Line(P const& a, P const& b) { first = a, second = b; }  
  const P& operator[] (int x) const { return x == 0 ? first : second; }
  P& operator[] (int x) { return x == 0 ? first : second; }
  Real length() const { return abs(second - first); }
};

typedef Line Segment;

struct Circle {
  P p; Real r;
  Circle(){}
  Circle(P const& p, Real r): r(r) { this->p = p; }
};

Real cross(P const& a, P const& b) { return imag(conj(a)*b); }
Real dot(P const& a, P const& b) { return real(conj(a)*b); }

bool intersect_lp(Line const& l, P const& p) {
  return abs(cross(l[1]-p, l[0]-p)) < EPS;
}

bool intersect_ll(Line const& l, Line const& m) {
  return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
         abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}

P projection(Line const& l, P const& p) {
  auto t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
  return l[0] + t*(l[0]-l[1]);
}

bool intersect_sp(Line const& s, P const& p) {
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}

Real distance_sp(Line const& s, P const& p) {
  P const r = projection(s, p);
  if(intersect_sp(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}

bool intersect_cs(Circle const& c, Line const& l) {
  return distance_sp(l, c.p) < c.r - EPS;
}

P crosspoint(const Line &l, const Line &m) {
  auto A = cross(l[1] - l[0], m[1] - m[0]);
  auto B = cross(l[1] - l[0], l[1] - m[0]);
  if(abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  if(abs(A) < EPS) assert(false && "PRECONDITION NOT SATISFIED");
  return m[0] + B / A * (m[1] - m[0]);
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

typedef double weight;
typedef vector<double> vec;
typedef vector<vec> matrix;

weight hungarian(const matrix &a) {
  int n = a.size(), p, q;
  vec fx(n, inf), fy(n, 0);
  vector<int> x(n, -1), y(n, -1);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      fx[i] = max(fx[i], a[i][j]);
  for (int i = 0; i < n; ) {
    vector<int> t(n, -1), s(n+1, i);
    for (p = q = 0; p <= q && x[i] < 0; ++p)
      for (int k = s[p], j = 0; j < n && x[i] < 0; ++j)
        if (abs(fx[k] + fy[j] - a[k][j]) < EPS && t[j] < 0) {
          s[++q] = y[j], t[j] = k;
          if (s[q] < 0)
            for (p = j; p >= 0; j = p)
              y[j] = k = t[j], p = x[k], x[k] = j;
        }
    if (x[i] < 0) {
      weight d = inf;
      for (int k = 0; k <= q; ++k)
        for (int j = 0; j < n; ++j)
          if (t[j] < 0) d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
      for (int j = 0; j < n; ++j) fy[j] += (t[j] < 0 ? 0 : d);
      for (int k = 0; k <= q; ++k) fx[s[k]] -= d;
    } else ++i;
  }
  weight ret = 0;
  for (int i = 0; i < n; ++i) ret += a[i][x[i]];
  return ret;
}

using namespace point_2d;

int main() {

  int N; cin >> N;

  Circle cs[2];
  rep(i, 2) cin >> cs[i].p >> cs[i].r;

  P rs[100]; rep(i, N) cin >> rs[i];
  P bs[100]; rep(i, N) cin >> bs[i];

  matrix dists(N, vector<double>(N, inf));

  rep(i, N) rep(j, N) {
    auto seg = Segment(rs[i], bs[j]);
    bool ok = 1;
    rep(k, 2) ok &= !intersect_cs(cs[k], seg);
    if(ok) dists[i][j] = min(dists[i][j], seg.length());
  }

  vector<vector<Segment>> min_rsegment(N, vector<Segment>(N, Segment(P(0,0), P(1,1))));
  vector<vector<Segment>> min_bsegment(N, vector<Segment>(N, Segment(P(0,0), P(1,1))));

  rep(i, N) rep(j, N) rep(k, 2) rep(l, 2) {

    auto& rpoint      = rs[i];
    auto& bpoint      = bs[j];
    auto& rtarcircle  = cs[k];
    auto& btarcircle  = cs[l];

    auto rtangents = tangent_points(rtarcircle, rpoint);
    auto btangents = tangent_points(btarcircle, bpoint);

    for(auto rtangent: rtangents) {
      for(auto btangent: btangents) {

        auto rtangent_line = Line(rpoint, rtangent);
        auto btangent_line = Line(bpoint, btangent);

        if(rpoint == rtangent) {
          rtangent_line = Line(rtangent, rtangent + (rtarcircle.p - rtangent) * P(0, 1));
        }

        if(bpoint == btangent) {
          btangent_line = Line(btangent, btangent + (btarcircle.p - btangent) * P(0, 1));
        }

        if(!intersect_ll(rtangent_line, btangent_line)) continue;

        auto purple_point = crosspoint(rtangent_line, btangent_line);
        auto rsegment = Segment(rpoint, purple_point);
        auto bsegment = Segment(bpoint, purple_point);

        bool intersect = 0;
        rep(x, 2) {
          intersect |= intersect_cs(cs[x], rsegment);
          intersect |= intersect_cs(cs[x], bsegment);
        }

        if(intersect) continue;
        dists[i][j] = min(dists[i][j], rsegment.length() + bsegment.length());
      }
    }
  }

  rep(i, N) rep(j, N) {
    if(dists[i][j] != inf)
      dists[i][j] = -dists[i][j];
  }

  auto r = hungarian(dists);

  if(r > 0) cout << -1 << endl;
  else      printf("%.10f\n", -r);

  return 0;
}