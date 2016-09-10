#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
typedef pair<int,int> P;
typedef pair<P,int> PP;
int h,w,n,N=1<<18;
P a[100000];

class StarrySkyTree{
public:
  int Mi[555555],A[555555];
  void init(){fill(Mi,Mi+555555,0);fill(A,A+555555,0);}
  void add(int a,int b,int x,int k=0,int l=0,int r=N) {
    if(r<=a||b<=l) return;
    if(a<=l&&r<=b){
      A[k]+=x;
      while(k){
        k=(k-1)/2;
        Mi[k]=min(Mi[k*2+1]+A[k*2+1],Mi[k*2+2]+A[k*2+2]);
      }
      return;
    }
    add(a,b,x,k*2+1,l,(l+r)/2);
    add(a,b,x,k*2+2,(l+r)/2,r);
  }
  int getMin(int a,int b,int k=0,int l=0,int r=N) {
    if(r<=a||b<=l)return 1<<29;
    if(a<=l&&r<=b)return Mi[k]+A[k];
    int left=getMin(a,b,k*2+1,l,(l+r)/2),right=getMin(a,b,k*2+2,(l+r)/2,r);
    return min(left,right)+A[k];
  }
};

StarrySkyTree t[2];
vector<PP> v[2][111111];
bool calc(int m) {
  t[0].init(),t[1].init();
  for(int i=0; i<h+w+2; i++) v[0][i].clear(),v[1][i].clear();
  for(int i=0; i<n; i++) {
    int o=(a[i].F+a[i].S)%2;
    int d1=a[i].F+a[i].S-m;
    int d2=a[i].F+a[i].S+m;
    int x=w-(a[i].S-a[i].F+o)/2-1,y=abs(d1)%2;
    d1=max(0,d1),d2=min(h+w,d2);
    x-=(m+y)/2;
    v[0][d1].push_back(PP(P(max(0,x+y),min(h+w,x+m+1)),1));
    v[0][d2+1].push_back(PP(P(max(0,x+y),min(h+w,x+m+1)),-1));
    v[1][d1].push_back(PP(P(max(0,x),min(h+w,x+m+y)),1));
    v[1][d2+1].push_back(PP(P(max(0,x),min(h+w,x+m+y)),-1));
  }
  int z=1,l=w-1,r=w;
  bool f=0,f2=0;
  for(int i=0; i<h+w; i++) {
    for(int k=0; k<2; k++) {
      for(int j=0; j<v[k][i].size(); j++) t[k].add(v[k][i][j].F.F,v[k][i][j].F.S,v[k][i][j].S);
    }
    z=min(z,t[i%2].getMin(l,r));
    if(i>=w-1) f=1;
    if(i>=h-1) f2=1;
    l+=f?(i%2?1:0):(i%2?0:-1);
    r+=f2?(i%2?0:-1):(i%2?1:0);
  }
  return z;
}

int main() {
  cin >> h >> w >> n;
  for(int i=0; i<n; i++) cin >> a[i].F >> a[i].S;
  int l=-1,r=h+w;
  while(l+1<r) {
    int m=(l+r)/2;
    if(calc(m)) r=m;
    else l=m;
  }
  cout << r << endl;
  return 0;
}
