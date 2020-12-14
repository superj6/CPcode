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

const int mxn = 250000;
int n;
ll dp[mxn], sz[mxn];
vector<int> g[mxn];

ll dfs(int c, int p){
	sz[c] = 1;
	for(int i : g[c]){
		if(i == p) continue;
		dp[c] += dfs(i, c);
		sz[c] += sz[i];
	}
	return dp[c] += sz[c] - 1;
}

ll dfs2(int c, int p){
	ll ret = dp[c];
	for(int i : g[c]){
		if(i == p) continue;
		sz[c] -= sz[i], dp[c] -= dp[i] + sz[i];
		sz[i] += sz[c], dp[i] += dp[c] + sz[c];
		ret = max(ret, dfs2(i, c));
		sz[i] -= sz[c], dp[i] -= dp[c] + sz[c];
		sz[c] += sz[i], dp[c] += dp[i] + sz[i];
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(0, -1);
	
	cout << n - 1 << " " << dfs2(0, -1) << endl;

	return 0;
}