#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> P;
int const R=1000;

int main(int argc, char *argv[])
{
  registerGen(argc, argv, 1);
  for (int t = 0; t < 30; t++) {
    ofstream of(format("02_random_%02d.in", t+1).c_str());
    int n, m, r;
    n = rnd.next(3, 30);
    m = rnd.next(n-1, min(300,n*(n-1)/2));
    r = rnd.next(10,R);
    
    vector<int> a(n-1), b(n-1);
    for (int i = 1; i < n; i++) {
      int par = rnd.next(0, i-1);
      a[i-1] = par; b[i-1] = i;
    }
    
    vector<int> node_num(n, -1);
    set<int> used; used.insert(-1);
    for (int i = 0; i < n; i++) {
      int v = -1;
      while (used.count(v) > 0) {
	v = rnd.next(1, n);
      }
      used.insert(v);
      node_num[i] = v;
    }

    set<P> used2;
	
    for (int i = 0; i < n-1; i++) {
      int aa = node_num[a[i]], bb = node_num[b[i]];
      if (aa >= bb) {
	swap(aa, bb);
      }
      used2.insert(P(aa,bb));
    }

    while(used2.size()!=m){
      int a=rnd.next(1,n-1),b=rnd.next(a+1,n);
      used2.insert(P(a,b));
    }
	
    int cost[30*29/2];
    for(int i=0;i<used2.size();i++)
      cost[i]=rnd.next(5,100);

    //r check
    int dp[30][30];
    for(int i=0;i<30;i++)
      for(int j=0;j<30;j++){
	if(i==j)dp[i][j]=0;
	else dp[i][j]=(1e9);
      }
	
    int idx;
    set<P>::iterator ite;
    for(ite=used2.begin(),idx=0;ite!=used2.end();ite++,idx++){
      dp[(*ite).first-1][(*ite).second-1]=cost[idx];
      dp[(*ite).second-1][(*ite).first-1]=cost[idx];
    }

    for(int k=0;k<n;k++)
      for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	  dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);

    if(dp[0][n-1]>R){t--;continue;}
    if(dp[0][n-1]>r)r=rnd.next(dp[0][n-1],1000);
    if(r>R) {t--;continue;};
    of << n << " " << m << " " << r << endl;

    of << 0 << ' ';
    for(int i=1;i<n-1;i++) of << rnd.next(0,10) << ' ';
    of << 0 << endl;
    
    // 連結になるように入力しないといけない。
    for(ite=used2.begin(),idx=0;ite!=used2.end();ite++,idx++){
      of << (*ite).first << ' ' << (*ite).second<< ' ';
      of << cost[idx] << endl;
    }    
    
    of.close();
  }
  return 0;
}
