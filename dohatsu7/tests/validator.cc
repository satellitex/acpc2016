#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N_MIN = 1;
const int N_MAX = 5000;
const int M_MIN = 1;
const int M_MAX = 100000;
const int c_MIN = 1;
const int c_MAX = 100000;

int main()
{
    registerValidation();
    
    int N, M;
    
    N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readEoln();
    
    int a[M_MAX], b[M_MAX], c[M_MAX];
    for (int i = 0; i < M; i++) {
        a[i] = inf.readInt(1, N, format("a[%d]", i+1));
        inf.readSpace();
        b[i] = inf.readInt(1, N, format("b[%d]", i+1));
        inf.readSpace();
        c[i] = inf.readInt(c_MIN, c_MAX, format("c[%d]", i+1));
        inf.readEoln();
    }
    inf.readEof();    
    return 0;
}
