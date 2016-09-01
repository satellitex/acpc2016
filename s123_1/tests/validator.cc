#include "testlib.h"
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int> > Graph;

// 制約
const int N_MIN = 3;
const int N_MAX = 30;
const int M_MIN = 2;
const int M_MAX = 300;
const int R_MIN = 10;
const int R_MAX = 1000;
const int C_MAX = 100;
const int C_MIN = 5;
// 入力変数
int n, m, r;
int a[M_MAX], b[M_MAX],c[M_MAX],d[N_MAX];

void input() {
  n = inf.readInt(N_MIN, N_MAX, "n");
  inf.readSpace();
  m = inf.readInt(M_MIN, min(M_MAX,n*(n-1)/2), "m");
  inf.readSpace();
  r = inf.readInt(R_MIN, R_MAX, "r");
  inf.readEoln();

  for (int i = 0; i < m; i++) {
    a[i] = inf.readInt(1, n-1, format("a[%d]", i + 1));
    inf.readSpace();
    b[i] = inf.readInt(a[i]+1, n, format("b[%d]", i + 1));
    inf.readSpace();
    c[i]= inf.readInt(C_MIN, C_MAX, format("c[%d]", i + 1));
    inf.readEoln();
  }

  for(int i=0;i<n;i++) {
    if(i)inf.readSpace();
    d[i] = inf.readInt(0, 10, format("d[%d]", i + 1));
  }
  inf.readEoln();
  inf.readEof();
}

void check() {
  
  // ai != bi
  for (int i = 0; i < n - 1; ++i) 
    ensuref(a[i] < b[i], "Input 'a[i]' and 'b[i]' must be 'a[i] < b[i]'");
  


  //多重辺がないか
  for(int i=0,AB[N_MAX][N_MAX]={};i<m;i++){
    ensuref(AB[a[i]-1][b[i]-1]==0, "Input 'tajuhen");
    AB[a[i]-1][b[i]-1]=1;
  }


  //連結かどうかと時間内でゴールまでいけるか。
  int G[N_MAX][N_MAX];
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++) G[i][j]=1e9*(i!=j);

  for(int i=0;i<m;i++) G[a[i]-1][b[i]-1]=G[b[i]-1][a[i]-1]=c[i];
  
  for(int k=0;k<n;k++)
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
  
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      ensuref(G[i][j]<1e9, "Input 'renketsu janaiyo");
  
  ensuref(G[0][n-1]<=r, "'G[0][n-1]>r'");
}

int main() {
  registerValidation();
  input();
  check();
  return 0;
}
