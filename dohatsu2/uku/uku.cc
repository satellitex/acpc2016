#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> P;

int H, W;
vector<string> F;

int gx, gy;

int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};
set< vector<string> > used;

bool solve()
{
  queue< vector<string> > que;
  used.insert(F), que.push(F);
  while(!que.empty()) {
    vector<string> f = que.front(); que.pop();
    /*
    for(int i = 0; i < H; i++) cout << f[i] << endl;
    cout << endl << endl;
    */
    if(f[gy][gx] == 'o') return true;
    
    for(int y = 0; y < H; y++) {
      for(int x = 0; x < W; x++) {
	if(f[y][x] != 'o') continue;
	for(int i = 0; i < 4; i++) {
	  vector<string> g = f;
	  
	  int px = x, py = y, nx = x + dx[i], ny = y + dy[i];
	  while(0 <= nx && nx < W && 0 <= ny && ny < H) {
	    swap(g[ny][nx], g[py][px]);
	    px = nx, py = ny;
	    nx += dx[i], ny += dy[i];	    
	  }
	  
	  if(!used.count(g)) used.insert(g), que.push(g);
	}
      }
    }
  }
  return false;
}

int main()
{
  cin >> H >> W;
  
  int cnt = 0;  
  F.resize(H + 1);
  for(int y = 0; y < H; y++) {
      cin >> F[y];
    for(int x = 0; x < W; x++) {
      if(F[y][x] == '@') F[y][x] = '.', gx = x, gy = y;
      else if(F[y][x] == 'o') cnt++;
    }
  }

  if(cnt > 2 && H > 1 && W > 1) cout << "yes" << endl;
  else cout << (solve() ? "yes" : "no") << endl;

  return 0;
}
