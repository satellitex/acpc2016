#include <cstdio>
#include <string>
#include<set>
#include <vector>
#include<cstdlib>
#include<cassert>
#include<cmath>
#include<cfloat>
#include<algorithm>
#include<iostream>
#include<sstream>
#include "testlib.h"

using namespace std;

void getSet(int &N, int &K){
  do{
    N=rnd.next(5, 100);
    K=rnd.next(2, N / 2);
  }while(__gcd(N,K)!=1||!(K<N/2)||K<2||N<5);
}

void randomCaseGenerator(const char *filename){
  int N,K;
  getSet(N,K);
  FILE *fp = fopen(filename, "w");
  fprintf(fp, "%d %d", N,K);
  fprintf(fp, "\n");
  fclose(fp);
}
string i2s(int x){
  stringstream ss;
  ss<<x;
  if(x<10) return "0"+ss.str();
  return ss.str();
}

int main() {

  for(int i=0;i<100;i++){
    string s="03_rand_small_"+i2s(i)+".in";
    randomCaseGenerator(s.c_str());
  }
  
}
