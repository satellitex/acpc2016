#include "testlib.h"
#include<cassert>
using namespace std;

static const int N_MIN = 5;
static const int N_MAX = 1000000;
static const int K_MIN = 2;
static const int K_MAX = 500000;
int main(){
  registerValidation();

  int N = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  int K = inf.readInt(K_MIN, K_MAX);
  inf.readEoln();
  inf.readEof();
  
  return 0;
}
