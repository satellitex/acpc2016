#include "testlib.h"

using namespace std;

const int S_LENGTH_MIN =      2;
const int S_LENGTH_MAX = 400000;

string S;

void input()
{
    S = inf.readToken(format("[a-z]{%d, %d}", S_LENGTH_MIN, S_LENGTH_MAX), "S");
    inf.readEoln();
    inf.readEof();
}

void check()
{
    ensuref(S.size() % 2 == 0, "The length of string must be even.");
}

int main()
{
    registerValidation();

    input();

    check();
    
    return 0;
}
