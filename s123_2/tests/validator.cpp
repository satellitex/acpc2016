#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// 制約
const int N_MIN = 1;
const int N_MAX = 15;
const int M_MIN = 1;
const int M_MAX = 10000;
const int K_MIN = 1;
const int K_MAX = 3;
const int a_MIN = 1;
const int a_MAX = 1000;
const int b_MIN = 1;
const int b_MAX = 10000;


// 入力変数
int n, m, k;
int a[N_MAX], b[N_MAX];

void input() {
  n = inf.readInt(N_MIN, N_MAX, "n");
  inf.readSpace();
  m = inf.readInt(M_MIN, min(M_MAX,n*(n-1)/2), "m");
  inf.readSpace();
  k = inf.readInt(K_MIN, K_MAX, "k");
  inf.readEoln();

  for (int i = 0; i <n; i++) {
    if(i)inf.readSpace();
    a[i] = inf.readInt(a_MIN, a_MAX, format("a[%d]", i + 1));
  }
  inf.readEoln();
  for(int i=0;i<n;i++){
    if(i)inf.readSpace();
    b[i] = inf.readInt(b_MIN, b_MAX, format("b[%d]", i + 1));
  }
  inf.readEoln();
  inf.readEof();
}

void check() {
    
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}
