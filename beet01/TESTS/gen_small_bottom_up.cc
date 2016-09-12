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

vector<pair<int, int>> nk_small_sets;

void getSet(int &N, int &K){
  static int idx = 0;
  do{
    if(nk_small_sets.size() <= idx) exit(0);
    tie(N, K) = nk_small_sets[idx++];
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

  for(int n=100; n<=300; n++) {
    for(int k=50; k<n/2; k++) {
      nk_small_sets.emplace_back(n, k);
    }
  }

  for(int i=0;i<100;i++){
    string s="04_small_bottom_up_"+i2s(i)+".in";
    randomCaseGenerator(s.c_str());
  }
  
}
