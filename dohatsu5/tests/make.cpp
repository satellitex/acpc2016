#include<bits/stdc++.h>
using namespace std;

int main(){

  std::mt19937 mt((int)time(0));

  cout<< 9 <<endl;
  for(int i=0;i<9;i++){
    cout<< mt() % 100 + 1<<endl;
  }
  return 0;
}
