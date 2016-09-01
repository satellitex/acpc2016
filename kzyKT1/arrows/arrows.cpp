#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{    
    ll n, d;
    cin >> n >> d; n--;
    ll N = n - d + 1;
    cout << (d == 1 ? n*(n+1)/2 : d+(N+3)*N/2-2) << endl;
    return 0;
}
