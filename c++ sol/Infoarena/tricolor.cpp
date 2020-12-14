	
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
 
const int mxn = 5000;
int n;
int sz[mxn];
int dp[mxn][mxn], dp2[mxn], f[mxn];
vector<int> g[mxn];
 
void dfs(int c, int p){
	sz[c] = 1, dp[c][0] = dp2[c] = 0;
	for(int i : g[c]){
		if(i == p) continue;
		dfs(i, c);
		
		for(int j = 1; j < sz[c] + sz[i]; j++) f[j] = dp[c][j - 1] + dp2[i] + j - 1;
		for(int j = sz[c] - 1; ~j; j--)
		for(int l = 1; l < sz[i]; l++){
			f[j + l] = max(f[j + l], dp[c][j] + dp[i][l] + j * l);
		}
		memcpy(dp[c], f, (sz[c] + sz[i]) * sizeof(int));
		
		int x = dp2[i] + 1;
		for(int j = 1; j < sz[i]; j++) x = max(x, dp[i][j] + j);
		dp2[c] += x;
		
		sz[c] += sz[i];
	}
}
 
void answer(){
	cin >> n;
	
	for(int i = 0; i < n; i++) g[i].clear();
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	memset(dp, 0xcf, sizeof(dp));
	dfs(0, -1);
	
	cout << max(*max_element(dp[0], dp[0] + n), dp2[0]) << endl;
}
 
int main(){
	freopen("tricolor.in", "r", stdin);
	freopen("tricolor.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();
	
	return 0;
}