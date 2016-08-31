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

using namespace std;

void getSet(int &X, int &Y){
  do{
    X=rand()%1000000;
    Y=rand()%500000;
  }while(__gcd(X,Y)!=1||X>Y/2||Y<2||X<5);
}

void randomCaseGenerator(const char *filename){
  int X,Y;
  getSet(X,Y);
  FILE *fp = fopen(filename, "w");
  fprintf(fp, "%d %d", X,Y);
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

  for(int i=0;i<30;i++){
    string s="02_rand_"+i2s(i)+".in";
    randomCaseGenerator(s.c_str());
  }
  
}
