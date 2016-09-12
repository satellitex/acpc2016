#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
struct edge{
  int p,l,r,f;
  edge(int p,int l,int r,int f):p(p),l(l),r(r),f(f){}
  bool operator<(const edge e)const{
    return p<e.p;
  }
};
vector<P> v;
vector<edge> e;
int n,m,k;
static const int MAX_SIZE = 1 << 17; 
int segMin[2][2 * MAX_SIZE - 1], segAdd[2][2 * MAX_SIZE - 1];
void add(int a, int b, int x, int w, int k = 0, int l = 0, int r = MAX_SIZE){
  if(a<0) a=0;
  if(b>MAX_SIZE) b=MAX_SIZE;
  if (r <= a || b <= l) return; 
  if (a <= l && r <= b){
    segAdd[w][k] += x;
    return;
  }
  add(a, b, x, w, k * 2 + 1, l, (l + r) / 2);
  add(a, b, x, w, k * 2 + 2, (l + r) / 2, r);
  segMin[w][k] = min(segMin[w][k * 2 + 1] + segAdd[w][k * 2 + 1],
		     segMin[w][k * 2 + 2] + segAdd[w][k * 2 + 2]);
}

int getMin(int a, int b, int w, int k = 0, int l = 0, int r = MAX_SIZE){
  if(a<0) a=0;
  if(b>MAX_SIZE) b=MAX_SIZE;
  if (r <= a || b <= l) return (MAX_SIZE);
  if (a <= l && r <= b) return (segMin[w][k] + segAdd[w][k]); 
  int left = getMin(a, b, w, k * 2 + 1, l, (l + r) / 2);
  int right = getMin(a, b, w, k * 2 + 2, (l + r) / 2, r);
  return (min(left, right) + segAdd[w][k]); 
}

bool check(int d){
  memset(segAdd,0,sizeof(segAdd));
  memset(segMin,0,sizeof(segMin));
  int i,j,a,b=0,g=d-1,p,q;
  e.clear();
  for(i=0;i<v.size();i++){
    int x=v[i].first,y=v[i].second;
    e.push_back(edge(x+y-d,n+y-x-d,n+y-x+d,1));
    e.push_back(edge(x+y+d+2,n+y-x-d,n+y-x+d,-1));
    e.push_back(edge(x+y-g,n+y-x-g,n+y-x+g,1));
    e.push_back(edge(x+y+g+2,n+y-x-g,n+y-x+g,-1));
  }
  //for(i=0;i<e.size();i++) cout << i << ":" << e[i].p <<":"<< e[i].l <<":"<< e[i].r <<":"<< e[i].f << endl;
  if(n%2){
    for(i=0;i<n+m;i++) add(i,i+1,MAX_SIZE,i%2);
  }else{
    for(i=0;i<n+m;i++) add(i,i+1,MAX_SIZE,(i+1)%2);
  }
  
  sort(e.begin(),e.end());
  for(i=0;i<e.size();i++){
    j=e[i].p;
    for(a=b;a<min(j,n+m-1);a++){
      if(a<n) p=a;
      else p=2*(n-1)-a;
      if(a<m) q=a;
      else q=2*(m-1)-a;
      int l=max(0,n-p),r=min(n+m-1,n+q);
      //cout << a << ":" << l << ":" << r << ":" << getMin(l,r+1,a%2) << endl;
      if(getMin(l,r+1,a%2)==0) return true;
    }
    while(1){
      if(i==e.size()||j!=e[i].p) break;
      add(e[i].l,e[i].r+1,e[i].f,(j+MAX_SIZE)%2);
      i++;
    }
    b=max(0,j);
    i--;
  }
  for(a=b;a<=n+m-2;a++){
      if(a<n) p=a;
      else p=2*(n-1)-a;
      if(a<m) q=a;
      else q=2*(m-1)-a;
      int l=max(0,n-p),r=min(n+m-1,n+q);
      //cout << a << ":" << l << ":" << r << ":" << getMin(l,r+1,a%2) << endl;
      if(getMin(l,r+1,a%2)==0) return true;
    }
  return false;
}
int main(){
  int i,j,x,y;
  cin>>n>>m>>k;
  for(i=0;i<k;i++){
    cin >> x >> y;
    v.push_back(P(x,y));
  }
  
  int l=0,r=n+m-2,mid;
  while(l+1<r){
    mid=(l+r)/2;
    //ccout << endl << l << ":" << r << ":" << mid << endl;
    if(check(mid)) l=mid;
    else r=mid;
  }
  if(k%n==0&&k/n==m) cout << 0 << endl;
  else cout << l+1 << endl;
  return 0;
}
