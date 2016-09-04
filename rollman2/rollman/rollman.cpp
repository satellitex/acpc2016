#include <bits/stdc++.h>
using namespace std;

int main(void){
	int X, Y, Z;
	cin >> X >> Y >> Z;

	int P;
	cin >> P;

	vector< vector< vector< int > > > S(Z, vector< vector<int> >(Y, vector<int>(X, 0) ) );

	for(int i = 0; i < P; i++){
		int x, y, z;
		cin >> x >> y >> z;
		S[z][y][x] = 1;
	}

	vector< vector<int> > net(Y, vector<int> (Y, 0));
	for(int y = 0; y < Y; y++){
		for(int x = 0; x < X; x++){
			cin >> net[y][x];
		}
	}

	int ans = 0;

	for(int z = 0; z < Z; z++){
		for(int y = 0; y < Y; y++){
			for(int x = 0; x < X; x++){
				if(net[y][x] == 1 && S[z][y][x] == 1){
					ans++;
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}
