#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100, k = 51;
int n, m, q, mod;
int g[mxn][mxn];
ll f[k][mxn][mxn], ff[k][mxn][mxn], fs[k][mxn][mxn], dp[k][mxn][mxn], s[k][mxn][mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> mod;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		g[--u][--v]++;
	}
	
	for(int i = 0; i < n; i++) f[0][i][i] = dp[0][i][i] = 1;
	
	for(int t = 1; t < k; t++){
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		for(int l = 0; l < n; l++){
			if(!~-t || i != l) (f[t][i][j] += f[t - 1][i][l] * g[l][j]) %= mod;
		}
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			for(int l = 1; l < t; l++){
				(ff[t][i][j] += s[l][i][j] * dp[t - l][j][i]) %= mod;
				(fs[t][i][j] += fs[l][i][j] * ff[t - l][i][j]) %= mod;
				(dp[t][i][j] += f[l][i][j] * ff[t - l][j][i]) %= mod;
				(s[t][i][j] += dp[l][i][j] * fs[t - l][j][i]) %= mod;
			}
			ff[t][i][j] = (mod + f[t][i][i] - ff[t][i][j]) % mod;
			(fs[t][i][j] += ff[t][i][j]) %= mod;
			dp[t][i][j] = (mod + f[t][i][j] - dp[t][i][j]) % mod;
			(s[t][i][j] += dp[t][i][j]) %= mod;
		}
	}
	
	cin >> q;
	
	while(q--){
		int x, y, t;
		cin >> x >> y >> t;
		cout << dp[t][--x][--y] << endl;
	}

	return 0;
}