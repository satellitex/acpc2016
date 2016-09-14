#include<bits/stdc++.h>
using namespace std;
int W,H,T,N;
int X[100],Y[100],tmp;

int cnt[100][100];

int main(){
  cin>>W>>H>>T>>N;
  for(int i=0;i<N;i++){
    cin>>X[i]>>Y[i]>>tmp;
    cnt[X[i]][Y[i]]++;
  }
  int ans=0;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      int num;
      cin>>num;
      if(num>0)ans+=cnt[j][i];
    }
  }
  cout<<ans<<endl;
  return 0;
}
