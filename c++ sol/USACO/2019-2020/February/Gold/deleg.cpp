#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
int dp[maxn];
vector<int> graph[maxn], g[maxn];

int dfs(int c, int p){
	int ret = 1;
	for(int i : graph[c]){
		if(i == p) continue;
		g[c].push_back(dfs(i, c));
		ret += g[c].back();
	}
	g[c].push_back(n - ret);
	return ret;
}

bool solve(int k){
	if((n - 1) % k) return 0;
	memset(dp, 0, k * sizeof(int));
	for(int c = 0; c < n; c++){
		int cnt = 0;
		for(int i : g[c]){
			int j = i % k;
			if(dp[k - j]) cnt--, dp[k - j]--;
			else if(j) cnt++, dp[j]++;
		}
		if(cnt) return 0;
	}
	return 1;
}

int main(){
	freopen("deleg.in", "r", stdin);
	freopen("deleg.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(0, -1);
	for(int i = 1; i < n; i++) cout << solve(i);
	cout << endl;

	return 0;
}