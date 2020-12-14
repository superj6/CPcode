#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 31333;
const int mxn = 3501;
int n, k;
int a[mxn], b[mxn];
int dp[mxn][mxn];
vector<int> g[mxn];

int dfs(int c, int p){
	dp[c][a[c]] = b[c] = 1;
	for(int i : g[c]){
		if(i == p) continue;
		(b[c] *= dfs(i, c)) %= mod;
		for(int j = k; ~j; j--){
			int ret = 0;
			for(int l = 0; l <= j; l++){
				(ret += dp[c][l] * dp[i][j - l]) %= mod;
			}
			(dp[c][j] = b[i] / 2 * dp[c][j] + ret) %= mod;
		}
	}
	return b[c] *= 2;
}

int main(){
	freopen("radare.in", "r", stdin);
	freopen("radare.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 0; i < n; i++) cin >> a[i];
	
	dfs(0, -1);
	
	cout << dp[0][k] << endl;

	return 0;
}