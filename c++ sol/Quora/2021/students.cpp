#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 3000, mxk = mxn * mxn;
int n, m, k;
int vis[mxk];
int dp[mxn][2];
vector<int> g[mxk];

int id(int x, int y){
	return n * x + y;
}

void dfs(int c){
	dp[0][1] = vis[c] = 1;
	int f[g[c].size()];
	for(int i : g[c]) if(!vis[i]){
		for(int j = 0; j < g[c].size(); j++) f[j] = vis[g[c][j]];
		dfs(i);
		int x = dp[i][1];
		for(int j = 0; j < g[c].size(); j++) x -= vis[g[c][j]] - f[j];
		dp[c][0] += max(dp[i][0], dp[i][1]);
		dp[c][1] += max(dp[i][0], x);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	k = n * n;
	
	for(int i = 0; i < m; i++){
		int x, y, X, Y;
		cin >> x >> y >> X >> Y;
		int u = id(--x, --y), v = id(--X, --Y);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	int ret = 0;
	for(int i = 0; i < k; i++){
		if(!vis[i]) dfs(i), ret += max(dp[i][0], dp[i][1]);
	}
	
	cout << ret << endl;
	
	return 0;
}