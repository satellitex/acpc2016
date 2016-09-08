#include "testlib.h"

using namespace std;

#define EPS (1e-8)

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
int bx[N_MAX], by[N_MAX];
int rx[N_MAX], ry[N_MAX];

struct Point {
    double x, y;
    Point () {}
    Point (double x, double y) : x(x), y(y) {}

    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }

    Point operator * (const double &k) const {
        return Point(x * k, y * k);
    }
};

struct Segment {
    Point s, t;
    Segment () {}
    Segment (Point s, Point t) : s(s), t(t) {}
};

struct Circle {
    Point p;
    double r;
    Circle (Point p, double r) : p(p), r(r) {}
};

bool isIntersectCP(const Circle &, const Point &);
bool contain_in_circle();
bool isIntersectCC(const Circle &, const Circle &);
bool isIntersectCLs(const Circle &, const vector<Segment> &);
bool isIntersectCL(const Circle &, const Segment &);

void input()
{
    n = inf.readInt(N_MIN, N_MAX);
    inf.readEoln();
    
    X1 = inf.readInt(X_MIN, X_MAX, "x_1");
    inf.readSpace();
    Y1 = inf.readInt(Y_MIN, Y_MAX, "y_1");
    inf.readSpace();
    R1 = inf.readInt(R_MIN, R_MAX, "r_1");
    inf.readEoln();

    X2 = inf.readInt(X_MIN, X_MAX, "x_2");
    inf.readSpace();
    Y2 = inf.readInt(Y_MIN, Y_MAX, "y_2");
    inf.readSpace();
    R2 = inf.readInt(R_MIN, R_MAX, "r_2");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        rx[i] = inf.readInt(RX_MIN, RX_MAX, format("rx[%d]", i + 1));
        inf.readSpace();
        ry[i] = inf.readInt(RX_MIN, RX_MAX, format("ry[%d]", i + 1));
        inf.readEoln();
    }

    for (int i = 0; i < n; i++) {
        bx[i] = inf.readInt(BX_MIN, BX_MAX, format("bx[%d]", i + 1));
        inf.readSpace();
        by[i] = inf.readInt(BX_MIN, BX_MAX, format("by[%d]", i + 1));
        inf.readEoln();
    }    
    inf.readEof();
}

void check()
{
    Circle c1(Point(X1, Y1), R1);
    Circle c2(Point(X2, Y2), R2);

    // Point contain in Circles
    ensuref(!contain_in_circle(), "Points are contained in circle");
    
    
    // two circles haven't common parts.
    ensuref(!isIntersectCC(c1, c2), "violates two circles haven't common parts.");

    
    vector<Segment> red(n), blue(n);
    for (int i = 0; i < n; i++) {
        red[i]  = Segment(Point(rx[i], ry[i]), Point(X1, Y1));
        blue[i] = Segment(Point(bx[i], by[i]), Point(X2, Y2));
    }
    
    // intersection blue oct body and red oct arms.
    ensuref(!isIntersectCLs(c2, red), "intersect blue oct body and red oct arm");
    
    // intersection red oct body and blue oct arms.
    ensuref(!isIntersectCLs(c1, blue), "intersect red oct body and blue oct arm");
}

int main()
{
    registerValidation();
    
    input();

    check();
    
    return 0;
}

double dot(const Point &a, const Point &b) { return a.x * b.x + a.y * b.y; }

double norm(const Point &p) { return dot(p, p); }

double abs(const Point &p) { return sqrt(norm(p)); }

bool isIntersectCP(const Circle &c, const Point &p)
{
    return (abs(c.p - p) < c.r + EPS);
}

bool contain_in_circle()
{
    Circle c1(Point(X1, Y1), R1);
    Circle c2(Point(X2, Y2), R2);
    for (int i = 0; i < n; i++) {
        if (isIntersectCP(c1, Point(rx[i], ry[i]))) return true;
        if (isIntersectCP(c2, Point(rx[i], ry[i]))) return true;
        if (isIntersectCP(c1, Point(bx[i], by[i]))) return true;
        if (isIntersectCP(c2, Point(bx[i], by[i]))) return true;       
    }
    return false;
}

bool isIntersectCC(const Circle &a, const Circle &b)
{
    double d = abs(a.p - b.p);
    return (d < a.r + b.r && d > abs(a.r - b.r) + EPS);
}

bool isIntersectCLs(const Circle &c, const vector<Segment> &ps)
{
    for (int i = 0; i < n; i++) {
        if (isIntersectCL(c, ps[i])) return true;
    }
    return false;
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

bool isIntersectCL(const Circle &c, const Segment &s)
{
    double d = distanceSP(s, c.p);
    return (d < c.r + EPS);
}
