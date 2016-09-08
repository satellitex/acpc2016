#include "testlib.h"

using namespace std;

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

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    for (int t = 0; t < 20; t++) {
        ofstream of(format("03_random_%02d.in", t+1).c_str());
        n = rnd.next(N_MIN, N_MAX);
        of << n << endl;

        X1 = rnd.next(X_MIN, X_MAX);
        Y1 = rnd.next(Y_MIN, Y_MAX);
        R1 = rnd.next(R_MIN, R_MAX);
        of << X1 << " " << Y1 << " " << R1 << endl;

        X2 = rnd.next(X_MIN, X_MAX);
        Y2 = rnd.next(Y_MIN, Y_MAX);
        R2 = rnd.next(R_MIN, R_MAX);
        of << X2 << " " << Y2 << " " << R2 << endl;

        for (int i = 0; i < n; i++) {
            rx[i] = rnd.next(RX_MIN, RX_MAX);
            ry[i] = rnd.next(RY_MIN, RY_MAX);
            of << rx[i] << " " << ry[i] << endl;
        }

        for (int i = 0; i < n; i++) {
            bx[i] = rnd.next(BX_MIN, BX_MAX);
            by[i] = rnd.next(BY_MIN, BY_MAX);
            of << bx[i] << " " << by[i] << endl;
        }
        of.close();
    }
    return 0;
}
