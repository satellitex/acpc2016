#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N_MIN =   2;
const int N_MAX = 300;
const int M_MIN =   0;
const int M_MAX = 300;
const int L_MIN =   0;
const int L_MAX = 300;
const int d_MIN =   0;
const int d_MAX =   4;
const int a_MIN =   1;
const int a_MAX = 300;
const int k_MIN =   1;
const int k_MAX = 300;
const int t_MIN =   1;
const int t_MAX = 100;

int N, M, L;
int d[N_MAX], a[N_MAX], k[N_MAX], t[N_MAX];

void input()
{      
    N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    M = inf.readInt(M_MIN, M_MAX, "M");
    inf.readSpace();
    L = inf.readInt(L_MIN, min(M, L_MAX), "L");
    inf.readEoln();

    for (int i = 0; i < M; i++) {
        d[i] = inf.readInt(d_MIN, d_MAX, format("d[%d]", i + 1));
        inf.readSpace();
        a[i] = inf.readInt(a_MIN, a_MAX, format("a[%d]", i + 1));
        inf.readSpace();
        k[i] = inf.readInt(k_MIN, k_MAX, format("k[%d]", i + 1));
        inf.readSpace();
        t[i] = inf.readInt(t_MIN, t_MAX, format("t[%d]", i + 1));
        inf.readEoln();
    }
    inf.readEof();
}

void check()
{
    for (int i = 0; i < N; i++) {
        ensuref(a[i] + k[i] - 1 <= N
                , "a[%d] equals %d and k[%d] equals %d, violates a[i] + k[i] - 1 <= N"
                , i + 1, a[i], i + 1, k[i]);
    }
}

int main()
{
    registerValidation();
    
    input();
    
    check();
    
    return 0;
}
