#include "testlib.h"

using namespace std;

const int S_MIN = 2;
const int S_MAX = 400000;

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);

    for (int t = 0; t < 20; t++) {
        ofstream of(format("03_random_%02d.in", t+1).c_str());
        
        PREV:;
        
        string S = rnd.next(format("[a-z]{%d, %d}", S_MIN, S_MAX));
        if (S.size() % 2 == 0) {
            of << S << endl;
        } else {
            goto PREV;
        }
            
        of.close();
    }


    return 0;
}
