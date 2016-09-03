#include "testlib.h"

using namespace std;

const int N_MIN =     1;
const int N_MAX =    15;
const int M_MIN =     1;
const int M_MAX = 10000;
const int K_MIN =     1;
const int K_MAX =     3;
const int a_MIN =     1;
const int a_MAX =  1000;
const int b_MIN =     1;
const int b_MAX = 10000;

int N, M, K;
int a[N_MAX], b[N_MAX];

void input()
{
  N = inf.readInt(N_MIN, N_MAX,"N");
  inf.readSpace();
  M = inf.readInt(M_MIN, M_MAX,"M");
  inf.readSpace();
  K = inf.readInt(K_MIN, min(N,K_MAX),"K");
  inf.readEoln();
  
  for (int i = 0; i < N; i++) {
    if (i > 0) inf.readSpace();
    a[i] = inf.readInt(a_MIN, a_MAX, format("a[%d]", i + 1));
  }
  inf.readEoln();

  for (int i = 0; i < N; i++) {
    if (i > 0) inf.readSpace();
    b[i] = inf.readInt(b_MIN, b_MAX, format("b[%d]", i + 1));
  }
  inf.readEoln();
  inf.readEof();
}

void check()
{
}

int main()
{
  registerValidation();
    
  input();

  check();
    
  return 0;
}
