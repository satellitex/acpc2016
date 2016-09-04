#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    
    int N, M, L;
    for (int t = 0; t < 15; t++) {
        ofstream of(format("03_random_%02d.in", t+1).c_str());
        N = rnd.next(2, 300);
        M = rnd.next(0, 300);
        L = rnd.next(1, M);
        of << N << " " << M << " " << L << endl;
        for (int i = 0; i < M; i++) {
            int d, a, k, t;
            d = rnd.next(0, 4);
            a = rnd.next(1, N);
            k = rnd.next(1, N - a + 1);
            t = rnd.next(1, 100);
            of << d << " " << a << " " << k << " " << t << endl;
        }
        of.close();
    }
    return 0;
}


