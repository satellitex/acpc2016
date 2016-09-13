#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> P;
typedef pair<P, int> PP;

const int INF = 1 << 25;

struct SegmentTree {
  vector<int> data;
  vector<int> prop;
  int sz;
  SegmentTree(int n)
  {
    sz = 1;
    while(sz < n) sz *= 2;
    data.resize(2*sz-1, 0);
    prop.resize(2*sz-1, 0);
  }
  void add(int a, int b, int x, int k, int l, int r)
  {
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) {
      prop[k] += x;
      return;
    }

    add(a, b, x, 2*k+1, l, (l+r)/2);
    add(a, b, x, 2*k+2, (l+r)/2, r);

    data[k] = min(data[2*k+1]+prop[2*k+1], data[2*k+2]+prop[2*k+2]);
  }
  void add(int a, int b, int x) {
    add(a, b, x, 0, 0, sz);
  }  
  int query(int a, int b, int k, int l, int r)
  {
    if(r <= a || b <= l) return INF;
    if(a <= l && r <= b) return data[k] + prop[k];
    
    int vl = query(a, b, 2*k+1, l, (l+r)/2);
    int vr = query(a, b, 2*k+2, (l+r)/2, r);
    
    return min(vl, vr) + prop[k];
  }
  int query(int a, int b)
  {
    return query(a, b, 0, 0, sz);
  }
};

int N, M, K;

vector<P> v;
//vector<P> pos;

bool check(int d)
{
  vector< vector<PP> > adder(N + M + 1);
  vector< vector<PP> > adder2(N + M + 1);

  for(int i = 0; i < v.size(); i++) {
    int x = v[i].first, y = v[i].second;
    int s = max(0, y - d), t = min(N + M, y + d + 1);
    //int l = x + pos[d].first, r = x + pos[d].second;
    int c = (y + d) % 2;
    int l = x - (d + c)/2, r = l + d + 1;
    adder[s].push_back(PP(P(max(0, l + c), min(N+M, r)), 1));
    adder[t].push_back(PP(P(max(0, l + c), min(N+M, r)), -1));
    adder2[s].push_back(PP(P(max(0, l), min(N+M, r - !c)), 1));
    adder2[t].push_back(PP(P(max(0, l), min(N+M, r - !c)), -1));
  }

  vector<SegmentTree> seg(2, N + M + 1);

  int a = M-1, b = M;
  for(int i = 0; i < N + M; i++) {
    for(int j = 0; j < adder[i].size(); j++) {
      PP p = adder[i][j], q = adder2[i][j];
      int l = p.first.first, r = p.first.second;
      int k = q.first.first, h = q.first.second;      
      seg[0].add(l, r, p.second);
      seg[1].add(k, h, q.second);
    }

    if(seg[i % 2].query(a, b) == 0) return true;

    if(!(i % 2) && i < M-1) a--;
    else if(i % 2 && i >= M-1) a++;
    if(i % 2 && i < N-1) b++;
    else if(!(i % 2) && i >= N-1) b--;
  }
  
  return false;
}

int main()
{
  cin >> N >> M >> K;
  for(int i = 0; i < K; i++) {
    int x, y; cin >> x >> y;
    v.push_back(P(M-(y-x+(x+y)%2)/2-1 , x + y));
  }
  /*
  int a = 0, b = 1;
  for(int i = 0; i < N+M; i++) {
    pos.push_back(P(a, b));
    if(i % 2) b++;
    else a--;
  }
  */
  int l = -1, r = N + M;
  while(l + 1 < r) {
    int m = (l + r) / 2;
    if(check(m)) l = m;
    else r = m;
  }
  
  cout << r << endl;
  
  return 0;
}
