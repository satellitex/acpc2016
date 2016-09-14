#include<bits/stdc++.h>
using namespace std;

int H,W;
char t[100][100];
int main(){

  srand( (int) time(0) );
  H = rand()%7 + 10;
  W = rand()%7 + 10;
  
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){

      if(rand()%5==0){
        t[i][j]='o';
      }else{
        t[i][j]='.';
      }
      
    }
  }

  t[ rand()%H ][ rand()%W ]='@';
  
  cout<<H<<' '<<W<<endl;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      cout<<t[i][j];
    }
    cout<<endl;
  }
  return 0;
}
