#include <bits/stdc++.h>
#include "../../testlib-0.9.5/testlib.h"
using namespace std;
typedef pair<int,int> P;

int main() {
  registerValidation();
  int n=inf.readInt(1, 50000, "n");
  inf.readSpace();
  int m=inf.readInt(1, 50000, "m");
  inf.readSpace();
  int k=inf.readInt(1, 100000, "k");
  inf.readEoln();
  set<P> s;
  for(int i=0; i<k; i++) {
    int x=inf.readInt(0, n-1, "x");
    inf.readSpace();
    int y=inf.readInt(0, m-1, "y");
    inf.readEoln();
    ensuref(!s.count(P(x,y)),"already exist");
    s.insert(P(x,y));
  }
  inf.readEof();
  return 0;
}
