#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX 400005

int bit[MAX];
void add(int i,int x){
  while(i<MAX){
    bit[i]+=x;
    i+=(i&-i);
  }
}

int sum(int i){
  int res=0;
  while(i>0){
    res+=bit[i];
    i-=(i&-i);
  }
  return res;
}

int n;
int t[MAX];
bool f[MAX];
vector<int> s[26];

ll solve(){
  for(int i=1;i<=n;i++){
    s[ t[i] ].push_back(i);
    add(i,1);
  }
  for(int i=0;i<26;i++){
    if(s[i].size()%2==1){
      return -1;
    }
  }
  ll ans=0;
  for(int i=1;i<=n;i++){
    if(f[i])continue;
    int ch=t[i];
    int target=s[ch].back();
    s[ch].pop_back();
    f[target]=true;
    ans+=sum(MAX-1);
    ans-=sum(target);
    add( target , -1 );
  }
  return ans;
}

char str[MAX];
int main(){
  scanf("%s",str);
  n=strlen(str);
  for(int i=0;i<n;i++)t[i+1]=(str[i]-'a');
  printf("%lld\n",solve());
  return 0;
}

