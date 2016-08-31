#include <bits/stdc++.h>
#define INF (INT_MAX/1000)
#define L_MAX 2001
#define d_MAX 2001
using namespace std;
int L, d;
double p;
vector<double> S;
vector<int> c;
vector<double> regsum;
double memo[L_MAX][d_MAX];

double getReg(int l, int r){
	double res = 0;
	for(int i = l; i < r; i++){
		res += 1 / S[i];
	}
	return res;
}

double func(int pos, int bar){
	if(memo[pos][bar] != -1) return memo[pos][bar];
	if(bar == d){
		return 0;
	}
	if(pos >= L){
		return INF;
	}
	double res = INF;
	res = func(pos+1, bar);
	if(pos+c[bar] <= L)
		res = min(res, func(pos+c[bar], bar+1) + regsum[pos+c[bar]] - regsum[pos]);
	return memo[pos][bar] = res;
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	for(int i = 0; i < L_MAX; i++) for(int j = 0; j < d_MAX; j++) memo[i][j] = -1;
	cin >> L >> p >> d;
	S.resize(L); c.resize(d); regsum.resize(L+1);
	for(int i = 0; i < L; i++){
		cin >> S[i];
	}
	for(int i = 0; i < d; i++){
		cin >> c[i];
	}
	regsum[0] = 0;
	for(int i = 1; i <= L; i++){
		regsum[i] = regsum[i-1] + (1 / S[i-1]);
	}
	printf("%.10f\n", p*func(0, 0));
}
