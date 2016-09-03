#include "testlib.h"

using namespace std;

const int N_MIN =       5;
const int N_MAX = 1000000;
const int K_MIN =       2;
const int K_MAX =  500000;

int N, K;

void input()
{    
    N = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    K = inf.readInt(K_MIN, K_MAX);

    inf.readEoln();
    inf.readEof();    
}

void check()
{        
    // K < N/2
    ensuref(K < (double)N/2, "K equals %d and N/2 equals %f, violates K < N/2"
                           , K, (double)N/2);   
    
    // N and K is disjoint
    ensuref(__gcd(N, K) == 1, "N equals %d and K equals %d, violates N and K is disjoint"
                            , N, K);    
}

int main()
{
    registerValidation();    
    
    input();
    
    check();
    
    return 0;
}
