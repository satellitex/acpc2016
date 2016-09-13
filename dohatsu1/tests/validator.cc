#include "testlib.h"

using namespace std;

const int N_MIN =    1;
const int N_MAX = 3000;

int N;
string dial[N_MAX];

void input()
{
  set<string> S;
  
    N = inf.readInt(N_MIN, N_MAX);
    inf.readEoln();
    for (int i = 0; i < N; i++) {
        dial[i] = inf.readToken(format("[0-9a-f]{%d, %d}", 5, 5), format("dial[%d]", i + 1));


        ensuref( S.count(dial[i]) == 0 , "%s is twice" , dial[i].c_str() );

        S.insert(dial[i]);
        inf.readEoln();
    }
    inf.readEof();
}

int to_num(char c)
{
    if (isdigit(c)) {
        return c - '0';
    } else {
        return c - 'a' + 10;
    }
}

void check()
{
    for (int i = 0; i < N; i++) {
        int odd = 0, even = 0;
        for (int j = 0; j < 5; j++) {
            if (to_num(dial[i][j]) % 2 == 0) {
                even++;
            } else {
                odd++;
            }
        }
        ensuref(even == 1 && odd == 4,
                "The number of even equals %d and odd equals %d, violates even = 1 and odd = 4"
                , even, odd);
    }
}

int main()
{
    registerValidation();
    input();
    check();
    return 0;
}
