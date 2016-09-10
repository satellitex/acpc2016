#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class BIT {
  public:
    int n;
    vector<int> bit;
    
    BIT(int N)
    {
        n = N + 1;
        bit.resize(n);
        for (int i = 0; i < n; i++) {
            bit[i] = 0;
        }
    }

    int sum(int i)
    {
	int s = 0;
	while (i > 0) {
	    s += bit[i];
	    i -= i & -i;
	}
	return s;
    }
  
    void add(int i, int x)
    {
	while (i <= n) {
	    bit[i] += x;
	    i += i & -i;
	}
    }
};

ll solve(string &S)
{
    int N = S.size();
    deque<int> pos[26];
    for (int i = 0; i < N; i++) {
        pos[S[i] - 'a'].push_back(i); 
    }
    for (int i = 0; i < 26; i++) {
        if (pos[i].size() & 1) return -1;
    }
    ll res = 0;
    vector<bool> used(N);
    BIT b(2*N);
    for (int i = 0; i < N; i++) {
        b.add(i + 1, +1);
    }        
    for (int i = 0; i < N; i++) {        
        int v = S[i] - 'a';       
        if (used[i]) continue;
        int pb = pos[v].back();
        pos[v].pop_front(); used[pb] = 1;        
        res += b.sum(2*N - i) - b.sum(pb + 1);
        b.add(pb + 1, -1);
        b.add(2*N - i, +1);
        pos[v].pop_back();
    }
    return res;
}

int main()
{
    string S;
    cin >> S;
    cout << solve(S) << endl;
    return 0;
}
