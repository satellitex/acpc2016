#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(){
  cout<<30<<" "<<29<<" "<<1000<<endl; 

  cout <<0<<" ";
  for(int i=0;i<28;i++){
    cout<<rnd.next(0,10)<<" ";
  }
  cout <<0<<endl;
  for(int i=1;i<=29;i++){
    cout << i <<" "<< i+1<<" "<<5<<endl;
  }

  return 0;
}
