#include <bits/stdc++.h>
#include "../../testlib-0.9.5/testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
  registerGen(argc, argv,1);
  for(int t=0; t<10; t++) {
    ofstream ofs(format("03_random_%02d.in",t).c_str());
    int n=rnd.next(2,1000000000);
    int d=rnd.next(1,n-1);
    ofs << n << " " << d << endl;
    ofs.close();
  }
  return 0;
}
