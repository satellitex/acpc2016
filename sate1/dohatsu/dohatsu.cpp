#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 100005
int N;
vector<int> G[MAX];
int tmp[MAX];
int sa[MAX];
int sb[MAX];

int search(int si,int d[MAX]){
  for(int i=0;i<MAX;i++)d[i]=-1;
  queue<int> Q;
  int ans=0,pos;
  d[si]=0;
  Q.push(si);
  while(!Q.empty()){
    pos=Q.front();Q.pop();
    for(int i=0;i<(int)G[pos].size();i++){
      int to=G[pos][i];
      if(d[to]!=-1)continue;
      d[to]=d[pos]+1;
      Q.push(to);
      ans=max(ans,d[to]);
    }
  }
  return pos;
}

int main(){
  scanf("%d",&N);
  for(int i=0;i<N-1;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    G[a].push_back(b);
    G[b].push_back(a);    
  }
  int A=search(1,tmp);
  int B=search(A,tmp);
  search(A,sa);
  search(B,sb);
  for(int i=1;i<=N;i++){
    printf("%d\n",(N-1)*2-max(sa[i],sb[i]));
  }
  return 0;
}
