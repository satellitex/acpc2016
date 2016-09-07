#include <bits/stdc++.h>
using namespace std;

struct Point{
    double x;
    double y;

    Point(double x, double y){
        this->x = x;
        this->y = y;
    }

    Point operator + (const Point &p){
        return Point(x+p.x, y+p.y);
    }
    Point operator - (const Point &p){
        return Point(x-p.x, y-p.y);
    }
    Point operator * (const double p){
        return Point(x*p, y*p);
    }
    double abs(){
        return sqrt(x*x + y*y);
    }
};

double cross(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}

Point intersection(Point p1, Point p2, Point q1, Point q2){
    /*
    Point b = b2 - b1;
    double d1 = abs(cross(b, a1-b1));
    double d2 = abs(cross(b, a2-b1));
    double t = d1 / (d1 + d2);

    return a1 + (a2 - a1) * t;
    */
    return p1 + ( p2 - p1 ) * ( cross( q2 - q1, q1 - p1 ) / cross( q2 - q1, p2 - p1 ) );
}

double getTriS(Point a, Point b, Point c){
    return (a.y*(b.x-c.x) + b.y*(c.x-a.x)+c.y*(a.x-b.x))/2.0;
}

int main(void){
    int N, K; cin >> N >> K;
    Point b1(1, 0);
    Point b2(cos(K*2*M_PI/(double)N), sin(K*2*M_PI/(double)N));
    Point a1(cos(2*M_PI/(double)N), sin(2*M_PI/(double)N));
    Point a2(cos((1-K)*2*M_PI/(double)N), sin((1-K)*2*M_PI/(double)N));

    Point p = intersection(b1, b2, a1, a2);
    double tri_S = getTriS(a1, b1, p)*N;

    double N_S = N*sin((2.0*M_PI)/N)/2.0;

    printf("%.8f\n", N_S - tri_S);

    return 0;
}
