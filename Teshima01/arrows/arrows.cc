#include <bits/stdc++.h>

using namespace std;

#define EPS (1e-8)

struct Point {
    double x, y;

    Point(){}
    Point(double x, double y) : x(x), y(y) {}

    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator * (const double &k) const { return Point(x * k, y * k); }
};

typedef Point Vector;

istream &operator >> (istream &is, Point &p)
{
    return is >> p.x >> p.y;
}

double dot(const Point &a, const Point &b)
{
    return a.x * b.x + a.y * b.y;
}

double cross(const Point &a, const Point &b)
{
    return a.x * b.y - b.x * a.y;
}

double norm(const Point &p)
{
    return dot(p, p);
}

double abs(const Point &p)
{
    return sqrt(norm(p));
}

double dist(const Point &a, const Point &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Point rotate90(const Point &p)
{
    return Point(-p.y, p.x);
}

struct Segment {
    Point s, t;
    Segment () {}
    Segment (Point s, Point t) : s(s), t(t) {}
};

typedef Segment Line;

bool isIntersectLL(const Line &a, const Line &b)
{
    return (abs(cross(a.t - a.s, b.t - b.s)) > EPS || 
	    abs(cross(a.t - a.s, b.t - b.s)) < EPS);  
}

Point crosspointLL(const Line &a, const Line &b)
{
    Vector va = a.t - a.s, vb = b.t - b.s;
    double d = cross(vb, va);
    if (abs(d) < EPS) return b.s;
    return a.s + va * cross(vb, b.t - a.s) * (1.0 / d);
}

struct Circle {
    Point p;
    double r;
    Circle () {}
    Circle (Point p, double r) : p(p), r(r) {}
};

istream &operator >> (istream &is, Circle &c)
{
    return is >> c.p.x >> c.p.y >> c.r;
}

vector<Point> tangentCP(const Circle &c, const Point &p)
{
    double x = norm(p - c.p);
    double d = x - c.r * c.r;
    if (d < -EPS) return vector<Point>();
    d = max(d, 0.0);
    Point p1 = (p - c.p) * (c.r * c.r / x);
    Point p2 = rotate90((p - c.p) * (-c.r * sqrt(d) / x));
    vector<Point> res;
    res.push_back(c.p + p1 - p2);
    res.push_back(c.p + p1 + p2);
    return res;
}

Point projection(const Segment &s, const Point &p)
{
    Point b = s.t - s.s;
    double t = dot(p - s.s, b) / norm(b);
    return s.s + b * t;
}

double distanceSP(const Segment &s, const Point &p)
{
    return abs(p - projection(s, p));
}

bool isIntersectCS(const Circle &c, const Segment &l)
{
    double d = distanceSP(l, c.p);
    return (d < c.r + EPS);
}

#define MAX_V 300
#define INF 1e9
typedef pair<double, int> P;

struct edge {
    int to, cap, rev;
    double cost;
    edge(int to, int cap, int rev, double cost) :
        to(to), cap(cap), rev(rev), cost(cost) {}
};

int V, prevv[MAX_V], preve[MAX_V];
double h[MAX_V], dst[MAX_V];
vector<edge> G[MAX_V];

void add_edge(int from, int to, int cap, double cost)
{
    G[from].push_back(edge(to, cap, G[to].size(), cost));
    G[to].push_back(edge(from, 0, G[from].size()-1, -cost));
}

double min_cost_flow(int s, int t, int f)
{
    double res = 0;
    fill(h, h+V, 0);
    while (f > 0) {
	priority_queue<P, vector<P>, greater<P> > Q;
	fill(dst, dst+V, INF);
	dst[s] = 0;
	Q.push(P(0, s));
	while (!Q.empty()) {
	    P p = Q.top(); Q.pop();
	    int v = p.second;
	    if (dst[v] < p.first) continue;
	    for (int i = 0; i < (int)G[v].size(); i++) {
		edge &e = G[v][i];
		if (e.cap > 0 && dst[e.to] > dst[v] + e.cost + h[v] - h[e.to] + EPS) {
		    dst[e.to] = dst[v] + e.cost + h[v] - h[e.to];
		    prevv[e.to] = v; preve[e.to] = i;
		    Q.push(P(dst[e.to], e.to));
		}
	    }
	}
	if (dst[t] == INF) return -1;
	for (int v = 0; v < V; v++) {
	    h[v] += dst[v];
	}
	int d = f;
	for (int v = t; v != s; v = prevv[v]) {
	    d = min(d, G[prevv[v]][preve[v]].cap);
	}
	f -= d;
	res += d * h[t];
	for (int v = t; v != s; v = prevv[v]) {
	    edge &e = G[prevv[v]][preve[v]];
	    e.cap -= d;
	    G[v][e.rev].cap += d;
	}
    }
    return res;
}

int main()
{
    int N;
    vector<Circle> c(2);
    cin >> N;
    for (int i = 0; i < 2; i++) {
        cin >> c[i];
    }
    vector<Point> r(N), b(N);
    for (int i = 0; i < N; i++) {
        cin >> r[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> b[i];
    }
    
    int S = N * 2, T = S + 1;
    V = N * 2 + 2;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Segment s(r[i], b[j]);
            double d = INF;            
            if (!isIntersectCS(c[0], s) && !isIntersectCS(c[1], s)) {
                d = min(d, dist(r[i], b[j]));
            }
            for (int k = 0; k < 2; k++) {
                vector<Point> vp1 = tangentCP(c[k], r[i]);
                vector<Point> vp2 = tangentCP(c[k], b[j]);
                for (int l = 0; l < (int)vp1.size(); l++) {
                    for (int m = 0; m < (int)vp2.size(); m++) {
                        Line l1(r[i], vp1[l]), l2(b[j], vp2[m]);
                        if (isIntersectLL(l1, l2)) {
                            Point cp = crosspointLL(l1, l2);
                            d = min(d, dist(r[i], cp) + dist(b[j], cp));
                        }
                    }
                }
            }
            if (d != INF) {
                add_edge(i, j + N, 1, d);
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        add_edge(S, i, 1, 0);
        add_edge(i + N, T, 1, 0);
    }
    double res = min_cost_flow(S, T, N);
    if (res == -1) {
        cout << -1 << endl;
    } else {
        printf("%.10f\n", res);
    }
    return 0;
}
