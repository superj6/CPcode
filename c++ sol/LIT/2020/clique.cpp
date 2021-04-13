#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int k = 20;

struct M{
	ll a[k][k];
	
	M(){ memset(a, 0, sizeof(a));}
	
	M friend operator*(M x, M y){
		M ret;
		for(int i = 0; i < k; i++)
		for(int j = 0; j < k; j++)
		for(int l = 0; l < k; l++){
			(ret.a[i][j] += x.a[i][l] * y.a[l][j]) %= mod;
		}
		return ret;
	}
};

int n, m;
ll a[k], v[k];
bool g[k][k];

M mpow(M x, ll y){
	M ret;
	for(int i = 0; i < k; i++) ret.a[i][i] = 1;
	for(; y; y >>= 1){
		if(y & 1) ret = ret * x;
		x = x * x;
	}
	return ret;
}

void dfs(int c){
	v[c] = 1;
	for(int i = 0; i < c; i++) if(g[c][i] && !v[i]) dfs(i);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		if(x < y) swap(x, y);
		g[--x][--y] = 1;
	}
	
	dfs(n - 1);
	
	ll ret = 1;
	for(int i = 1; i < n; i++) if(v[i]){
		M dp;
		dp.a[0][0] = g[i][0];
		for(int j = 1; j <= i; j++){
			dp = mpow(dp, a[j] / a[j - 1]);
			if(g[i][j]) for(int l = 0; l <= j; l++) (++dp.a[j][l]) %= mod;
		}
		ll x = 0;
		for(int j = 0; j <= i; j++) (x += dp.a[j][0]) %= mod;
		(ret *= x) %= mod;
	}
	
	cout << ret << endl;

	return 0;
}