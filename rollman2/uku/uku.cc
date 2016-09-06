#include <bits/stdc++.h>

using namespace std;

int main()
{
  int X, Y, Z;
  cin >> X >> Y >> Z;

  int p; cin >> p;
  int net[55][55];
  for(int i = 0; i < p; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    net[b][a]++;
  }
  
  int get = 0;
  for(int i = 0; i < Y; i++) {
    for(int j = 0; j < X; j++) {
      int s; cin >> s;
      if(s == 1) get += net[i][j];
    }
  }

  cout << get << endl;
  
  return 0;
}
