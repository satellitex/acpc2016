#include<bits/stdc++.h>
using namespace std;
#define MAX 10000001
int num[MAX];

int main(){
  fill(num,num+MAX,1);
  for(int i=2;i*i<MAX;i++){
    if(num[i]>1)continue;
    for(int j=i*i;j<MAX;j+=i){
      num[j]=i;
    }
  }

  map<int,int> mp;
  int n,x;
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>x;
    while(num[x]!=1){
      mp[ num[x] ]++;
      x/=num[x];
    }
    if(x>1)mp[x]++;
  }

  long long ans=1;
  long long mod=1e9+7;

  for(auto it : mp ){
    ans = ( ans * (long long)(it.second+1) ) % mod;
  }

  cout<<ans<<endl;
  return 0;
}

