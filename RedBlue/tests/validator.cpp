#include "testlib.h"
#include <bits/stdc++.h>

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

    set< pair<double,double> > st;
    
    for (int i = 0; i < n; i++) {
        rx[i] = inf.readInt(RX_MIN, RX_MAX, format("rx[%d]", i + 1));
        inf.readSpace();
        ry[i] = inf.readInt(RX_MIN, RX_MAX, format("ry[%d]", i + 1));
        inf.readEoln();

        st.insert( make_pair(rx[i],ry[i]) );
        
    }

    for (int i = 0; i < n; i++) {
        bx[i] = inf.readInt(BX_MIN, BX_MAX, format("bx[%d]", i + 1));
        inf.readSpace();
        by[i] = inf.readInt(BX_MIN, BX_MAX, format("by[%d]", i + 1));
        inf.readEoln();

        st.insert( make_pair(bx[i],by[i]) );
    }

    assert( (int)st.size() == n+n );
    
    inf.readEof();
}

int main()
{
    registerValidation();
    
    input();
    
    return 0;
}
