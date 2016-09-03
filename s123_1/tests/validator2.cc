#include "testlib.h"
#include <set>

using namespace std;

const int N_MIN =    3;
const int N_MAX =   30;
const int M_MIN =    2;
const int M_MAX =  300;
const int R_MIN =   10;
const int R_MAX = 1000;
const int a_MIN =    1;
const int a_MAX =   30;
const int b_MIN =    2;
const int b_MAX =   30;
const int c_MIN =    5;
const int c_MAX =  100;
const int d_MIN =    0;
const int d_MAX =   10;

int N, M, R;
int a[M_MAX], b[M_MAX], c[M_MAX];
int d[N_MAX];

bool reachable(int&);
bool check_multiple_edge(void);

void input()
{
    N = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    M = inf.readInt(M_MIN, M_MAX);
    inf.readSpace();
    R = inf.readInt(R_MIN, R_MAX);
    inf.readEoln();

    for (int i = 0; i < M; i++) {
        a[i] = inf.readInt(a_MIN, a_MAX, format("a[%d]", i + 1));
        inf.readSpace();
        b[i] = inf.readInt(b_MIN, b_MAX, format("b[%d]", i + 1));
        inf.readSpace();
        c[i] = inf.readInt(c_MIN, c_MAX, format("c[%d]", i + 1));
        inf.readEoln();
    }
    for (int i = 0; i < N; i++) {
        if (i > 0) inf.readSpace();
        d[i] = inf.readInt(d_MIN, d_MAX, format("d[%d]", i + 1));
    }
    inf.readEoln();
    inf.readEof();
}

void check()
{
    // N - 1 <= M <= min(M_MAX, N * (N - 1) / 2)
    ensuref(N - 1 <= M && M <= N * (N - 1) / 2,
            "N equals %d and M equals %d, violates N - 1 <= M <= N * (N - 1) / 2"
            , N, M);
    
    
    for (int i = 0; i < M; i++) {
        // 1 <= a[i] < b[i] <= N
        ensuref(1 <= a[i] && a[i] < b[i] && b[i] <= N,
                "N equals %d, a[%d] equals %d and b[%d] equals %d, violates 1 <= a[i] < b[i] <= N"
                , N, i + 1, a[i], i + 1, b[i]);
    }

    
    // d1 = dN = 0
    ensuref(d[0]   == 0, "d[1] equals %d, violates d[1] = 0", d[0]);
    ensuref(d[N-1] == 0, "d[N] equals %d, violates d[N] = 0", d[N-1]);

    
    int t;
    // reachable from 1 to N within R min
    ensuref(reachable(t), "minimum time is %d and unreachable within R min", t);

    
    // multiple edge check
    ensuref(!check_multiple_edge(), "Multiple edge is exist");
}

int main()
{
    registerValidation();

    input();

    check();
    
    return 0;
}

bool reachable(int &t)
{
    const int INF = (1<<29);
    int dist[N_MAX][N_MAX];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }

    for (int i = 0; i < M; i++) {
        dist[a[i]-1][b[i]-1] = dist[b[i]-1][a[i]-1] = c[i];
    }

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = min(dist[i][j],
                                 dist[i][k] + dist[k][j]);
            }
        }
    }
    return (dist[0][N-1] <= R);
}

bool check_multiple_edge()
{
    set< pair<int, int> > used;
    for (int i = 0; i < M; i++) {
        if (used.count(make_pair(a[i], b[i]))) {
            return true;
        }
        used.insert(make_pair(a[i], b[i]));
    }
    return false;
}
