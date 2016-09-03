#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    
    for (int t = 0; t < 10; t++) {
        ofstream of(format("04_max_%02d.in", t+1).c_str());
        int N, M;
        N = rnd.next(5000, 5000);
        M = rnd.next(100000, 100000);
        of << N << " " << M << endl;
        for (int i = 0; i < M; i++) {
            int a, b, c;
            a = rnd.next(1, N-1);
            b = rnd.next(1, N);
            c = rnd.next(1, 100000);
            of << a << " " << b << " " << c << endl;
        }        
        of.close();
    }        
    return 0;
}