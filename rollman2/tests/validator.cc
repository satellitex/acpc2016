#include "testlib.h"
#include <set>

using namespace std;

const int X_MIN =  1;
const int X_MAX = 50;
const int Y_MIN =  1;
const int Y_MAX = 50;
const int Z_MIN =  1;
const int Z_MAX = 50;
const int p_MIN =  0;
const int p_MAX = 50;
const int a_MIN =  0;
const int a_MAX = 49;
const int b_MIN =  0;
const int b_MAX = 49;
const int c_MIN =  0;
const int c_MAX = 49;
const int s_MIN =  0;
const int s_MAX =  1;

int X, Y, Z, p;
int a[p_MAX], b[p_MAX], c[p_MAX];
int s[Y_MAX][X_MAX];

void input()
{
    X = inf.readInt(X_MIN, X_MAX, "X");
    inf.readSpace();
    Y = inf.readInt(Y_MIN, Y_MAX, "Y");
    inf.readSpace();
    Z = inf.readInt(Z_MIN, Z_MAX, "Z");
    inf.readEoln();

    p = inf.readInt(p_MIN, p_MAX, "p");
    inf.readEoln();

    for (int i = 0; i < p; i++) {
        a[i] = inf.readInt(a_MIN, min(a_MAX, X), format("a[%d]", i));
        inf.readSpace();
        b[i] = inf.readInt(b_MIN, min(b_MAX, Y), format("b[%d]", i));
        inf.readSpace();
        c[i] = inf.readInt(c_MIN, min(c_MAX, Z), format("c[%d]", i));
        inf.readEoln();
    }
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (j > 0) inf.readSpace();
            s[i][j] = inf.readInt(s_MIN, s_MAX, format("s[%d][%d]", j, i));
        }
        inf.readEoln();
    }
    inf.readEof();
}

void check()
{
    // duplicate
    typedef pair<int, int> pii;
    typedef pair<pii, int> P;
    set<P> used;
    bool satisfaction = 1;
    for (int i = 0; i < p; i++) {
        P n(pii(a[i], b[i]), c[i]);
        if (used.count(n)) {
            satisfaction = 0;
        }
        used.insert(n);
    }

    ensuref(satisfaction, "Exist duplicate coordinate");
}

int main()
{
    registerValidation();

    input();

    check();
    
    return 0;
}
