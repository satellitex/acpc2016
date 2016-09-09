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

Real distance_lp(Line const& l, P const& p) {
  return abs(p - projection(l, p));
}

bool intersect_cs(Circle const& c, Line const& l) {
  if(abs(l[0] - c.p) < c.r - EPS && abs(l[1] - c.p) < c.r - EPS) { return false; }
  return distance_lp(l, c.p) < c.r - EPS;
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

namespace flow {

struct edge {
  int to; double cap, cost, rev;
  edge(int t, double ca, double co, int r) : to(t), cap(ca), cost(co), rev(r) {}
};

struct primal_dual {
  
  vector<vector<edge>> G;
  vector<double> h;
  vector<double> dist;
  vector<double> prevv, preve;
  
  primal_dual(int V) : G(V), h(V), dist(V), prevv(V), preve(V) {}
  
  void add_edge(int from, int to, int cap, double cost) {
    G[from].emplace_back(to, cap, cost, G[to].size());
    G[to].emplace_back(from, 0, -cost, G[from].size()-1);
  }
  
  double min_cost_flow(int s, int t, double f) {
    double ret = 0;
    fill(h.begin(), h.end(), 0);
    while(f > 0) {
      typedef pair<double, int> P;
      priority_queue<P, vector<P>, greater<P>> pq;
      fill(dist.begin(), dist.end(), inf);
      dist[s] = 0;
      pq.emplace(0, s);
      while(!pq.empty()) {
        P p = pq.top(); pq.pop();
        int v = p.second;
        if(dist[v] < p.first) continue;
        for(int i=0; i<G[v].size(); i++) {
          auto& e = G[v][i];
          if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v;
            preve[e.to] = i;
            pq.emplace(dist[e.to], e.to);
          }
        }
      }

      if(dist[t] == inf) return -1;
      for(int i=0; i<h.size(); i++) h[i] += dist[i];

      double d = f;
      for(int i=t; i!=s; i=prevv[i]) {
        d = min(d, G[prevv[i]][preve[i]].cap);
      }
      f -= d;
      ret += d * h[t];
      for(int i=t; i!=s; i=prevv[i]) {
        auto& e = G[prevv[i]][preve[i]];
        e.cap -= d;
        G[i][e.rev].cap += d;
      }
    }
    return ret;
  }

};

}

int main() {

  int N; cin >> N;

  Circle cs[2];
  rep(i, 2) cin >> cs[i].p >> cs[i].r;

  P rs[100]; rep(i, N) cin >> rs[i];
  P bs[100]; rep(i, N) cin >> bs[i];

  flow::primal_dual pd(2 * N + 2);
  int const SRC = 2 * N;
  int const SINK = 2 * N + 1;

  rep(i, N) rep(j, N) {
    auto seg = Segment(rs[i], bs[j]);
    bool ok = 1;
    rep(k, 2) if(intersect_cs(cs[k], seg)) ok = 0;
    if(ok) pd.add_edge(i, N + j, 1, abs(seg[1] - seg[0]));
  }

  rep(i, N) rep(j, N) rep(k, 2) rep(l, 2) {
    auto rps = tangent_points(cs[k], rs[i]);
    auto bps = tangent_points(cs[l], bs[j]);
    for(auto rc: rps) for(auto bc: bps) {
      auto rtanline = Line(rs[i], rc);
      auto btanline = Line(bs[j], bc);

      if(rtanline[0] == rtanline[1])  
        rtanline = Line(rtanline[0], rtanline[0] + (cs[k].p - rtanline[0]) * P(0, 1));

      if(btanline[0] == btanline[1])
        btanline = Line(btanline[0], btanline[0] + (cs[l].p - btanline[0]) * P(0, 1));

      bool ok = 1;
      rep(x, 2) if(intersect_cs(cs[x], rtanline)) ok = 0;
      rep(x, 2) if(intersect_cs(cs[x], btanline)) ok = 0;
      if(!ok) continue;

      if(intersect_ll(rtanline, btanline)) {
        auto purple_p = crosspoint(rtanline, btanline);
        auto len = abs(purple_p - rs[i]) + abs(purple_p - bs[j]);
        pd.add_edge(i, N + j, 1, len);
      }
    }
  }

  rep(i, N) {
    pd.add_edge(SRC, i, 1, 0);
    pd.add_edge(N + i, SINK, 1, 0);
  }
  
  auto r = pd.min_cost_flow(SRC, SINK, N);  
  if(r < 0) cout << -1 << endl;
  else      printf("%.10f\n", r);
  
  return 0;
}