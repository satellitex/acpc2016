#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
  registerGen(argc,argv,1);
  for (int t=0;t<40;t++) {
    ofstream of(format("03_random_%02d.in",t+1).c_str());
    int n,m,k;
    n=rnd.next(1, 15);
    m=rnd.next(1, 10000);
    k=rnd.next(1,min(n,3));
    of<<n<<' '<<m<<' '<<k<<endl;
    for(int i=0;i<n;i++){
      if(i)of<<' ';
      of<<rnd.next(1,1000);
    }
    of<<endl;
    for(int i=0;i<n;i++){
      if(i)of<<' ';
      of<<rnd.next(1,10000);
    }
    of<<endl;
  }
  return 0;
}
