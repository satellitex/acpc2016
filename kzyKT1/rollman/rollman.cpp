#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll d;

ll c(ll a, ll b){
    ll res = 1;
    for(ll i = 0; i < b; i++){
        res *= a-i;
    }
    for(ll i = 1; i <= b; i++){
        res /= i;
    }
    return res;
}

int main(void){
    cin >> n >> d;
    ll ans = 0;
    if(d != 1){
        ans += d;
        n -= d+1;

        ans += 3*n + n*(n-1)/2;

        /*
        for(int i = 0; i < n; i++){
            ans += 3 + i;
        }
        while(n){
            ans += 3;
            g++;
            n--;
        }
        */
    }else{
        ans = c(n, 2);
    }
    cout << ans << endl;
}
