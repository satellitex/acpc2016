#include <bits/stdc++.h>
#include "../../testlib-0.9.5/testlib.h"
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
const int N=50000;

int main(int argc, char* argv[]) {
  registerGen(argc, argv,1);
  for(int t=0; t<20; t++) {
    ofstream ofs(format("03_random_%02d.in",t).c_str());
    int n=rnd.next(1,N),m=rnd.next(1,N);
    int k=rnd.next(1,(int)min((ll)n*m,(ll)100000));
    ofs << n << " " << m << " " << k << endl;
    int x=rnd.next(0,n-1),y=rnd.next(0,m-1);
    ofs << x << " " << y << endl;
    set<P> s;
    s.insert(P(x,y));
    for(int i=1; i<k; i++) {
      int xx=x,yy=y;
      while(s.count(P(xx,yy))) xx=rnd.next(0,n-1),yy=rnd.next(0,m-1);
      ofs << xx << " " << yy << endl;
      s.insert(P(xx,yy));
    }
    ofs.close();
  }
  return 0;
}
