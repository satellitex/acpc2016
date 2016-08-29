#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    registerValidation();
    int N, M, L;
    
    N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    M = inf.readInt(0, 1000, "M");
    inf.readSpace();
    L = inf.readInt(0, M, "L");
    inf.readEoln();
    
    int d, a, k, t;
    for (int i = 0; i < M; i++) {
        d = inf.readInt(0, 4);
        inf.readSpace();
        a = inf.readInt(1, N);
        inf.readSpace();
        k = inf.readInt(1, N - a + 1);
        inf.readSpace();
        t = inf.readInt(1, 100);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
