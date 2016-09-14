#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;

int N,M,K;
P a[20];

int main(){
  cin>>N>>M>>K;
  for(int i=0;i<N;i++)cin>>a[i].first;
  for(int i=0;i<N;i++)cin>>a[i].second;
  sort(a,a+N);
  reverse(a,a+N);
  
  int ans=M;
  for(int bit=0;bit<(1<<N);bit++){
    if( __builtin_popcount(bit) > K ){
      continue;
    }
    int cnt=M;
    int sum=0;
    for(int i=0;i<N;i++){
      if(bit>>i&1){
        int c=min(cnt,a[i].second);
        cnt-=c;
        sum+=c*a[i].first;
      }
    }
    ans=max(ans,cnt+sum);
  }
  cout<<ans<<endl;
  return 0;
}
