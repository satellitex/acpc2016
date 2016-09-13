#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

int main(){
  for(int i=0;i<100000;i++){
    int id = rand();
    char ch = 'a'+(id%10);
    cout<<ch<<ch;
  }

  for(int i=0;i<100000;i++){
    int id = rand();
    char ch = 'a'+(id%10+10);
    cout<<ch<<ch;
  }
  cout<<endl;
  return 0;
}
