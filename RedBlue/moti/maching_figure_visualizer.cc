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

////////////////////////////////////
ofstream ofs;
double zoom = 1;
////////////////////////////////////

string random_color() {
  stringstream ss; ss << std::hex << rndgen.next(16777216);
  return "#" + ss.str();
}

ostream& set_offset(P p) {
  return ofs << "set_offset(" << p.real() << "," << p.imag() << ")" << endl;
}

ostream& line(Line l, string color = "") {
  l[0] *= zoom, l[1] *= zoom;
  return ofs << "line(" << l[0].real() << "," << l[0].imag() << ","
    << l[1].real() << "," << l[1].imag() << ","
    << (color.empty() ? "\"" + random_color() + "\"" : "\"" + color + "\"") << ")"
    << endl;
}

ostream& circle(Circle c, string color = "") {
  c = Circle(P(c.p.real() * zoom, c.p.imag() * zoom), c.r * zoom);
  return ofs << "circle(" << c.p.real() << "," << c.p.imag() << "," << c.r << ","
  << (color.empty() ? "\"" + random_color() + "\"" : "\"" + color + "\"") << ")" << endl;
}

ostream& plot(P p, string color = "") {
  auto c = Circle(P(p.real() * zoom, p.imag() * zoom), 0.05 * zoom);
  return ofs << "circle(" << c.p.real() << "," << c.p.imag() << "," << c.r << ","
  << (color.empty() ? "\"" + random_color() + "\"" : "\"" + color + "\"") << ", true)" << endl;
}

void show_picture() {
  ofs.close();
  int r = system("open visualizer.html");
  assert(!WEXITSTATUS(r));
}

////////////////////////////////////////////////////

void init() {
  ofs = ofstream("data.js");
}

void set_grid() {
  int Min = -100, Max = +100;
  for(int i=Min; i<Max; i++) {
    line(Line(P(i, -1000), P(i, 1000)), "#eeeeee");
    line(Line(P(-1000, i), P(1000, i)), "#eeeeee");
  }
}

}

map<string, double> parse_settings(ifstream& ifs) {
  map<string, double> ret;
  string query;
  while(getline(ifs, query)) {
    stringstream ss(query);
    string name, val_str;
    getline(ss, name, ',');
    getline(ss, val_str);
    ret[name] = stod(val_str);
  }
  return ret;
}


int main() {

  using namespace visualizer;
  init();
  {
    ifstream ifs("settings.txt");
    auto settings = parse_settings(ifs);

    if(settings.find("zoom") != settings.end()) {
      zoom = settings["zoom"];
    }

    if(settings.find("offx") != settings.end()) {
      double offx = settings["offx"];
      double offy = settings["offy"];
      set_offset(P(offx, offy));
//      cout << zoom << ", " << offx << ", " << offy << endl;
    } else {
      auto center = P();//(cs[0].p + cs[1].p) / 2.0;
      set_offset(center);
    }
  }
  set_grid();

  int N; cin >> N;

  Circle cs[2];
  rep(i, 2) cin >> cs[i].p >> cs[i].r;

  P rs[100]; rep(i, N) cin >> rs[i];
  P bs[100]; rep(i, N) cin >> bs[i];

  vector<vector<Segment>> min_rsegment(N, vector<Segment>(N, Segment(P(0,0), P(1,1)))); // ここで斜めのゴミ線分を作ってるので注意
  vector<vector<Segment>> min_bsegment(N, vector<Segment>(N, Segment(P(0,0), P(1,1))));

  vector<vector<double>> dists(N, vector<double>(N, inf));

  rep(i, N) rep(j, N) {
    auto seg = Segment(rs[i], bs[j]);
    bool ok = 1;
    rep(k, 2) {
      ok &= !intersect_cs(cs[k], seg);
    }

    if(ok) {
      dists[i][j] = min(dists[i][j], seg.length());
      min_rsegment[i][j] = seg;
      min_bsegment[i][j] = Segment(P(),P());
    }
  }

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

        if(!intersect_ll(rtangent_line, btangent_line))
          continue;

        auto purple_point = crosspoint(rtangent_line, btangent_line);
        auto rsegment = Segment(rpoint, purple_point);
        auto bsegment = Segment(bpoint, purple_point);

        bool intersect = 0;
        rep(x, 2) {
          intersect |= intersect_cs(cs[x], rsegment);
          intersect |= intersect_cs(cs[x], bsegment);
        }

        if(intersect)
          continue;

        auto length = rsegment.length() + bsegment.length();
        if(dists[i][j] > length) {
          dists[i][j] = min(dists[i][j], length);
          min_rsegment[i][j] = rsegment;
          min_bsegment[i][j] = bsegment;
        }

      }
    }
  }

  int par[N];
  rep(i, N) par[i] = i;

  vector<Segment> segments_to_draw;
  double ans = inf;
  do {
    vector<Segment> cand;
    double sum = 0.0;
    rep(i, N) {
      sum += dists[i][par[i]];
      cand.push_back(min_rsegment[i][par[i]]);
      cand.push_back(min_bsegment[i][par[i]]);
    }
    if(ans > sum) {
      ans = sum;
      segments_to_draw = cand;
    }
  } while(next_permutation(par, par + N));
  
  for(auto& line: segments_to_draw) {
    visualizer::line(line, "#ff88ff");
  }

  visualizer::circle(cs[0], "#ff0000"); // 赤いタコ
  visualizer::circle(cs[1], "#0000ff"); // 青いタコ
  rep(i, N) plot(rs[i], "#ff0000"), plot(bs[i], "#0000ff"); // 赤いタコの足、青いタコの足
  visualizer::show_picture();

  return 0;
}