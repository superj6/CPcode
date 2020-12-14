#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, int>
#define f first
#define s second

const int mxn = 100000;
int n;
ll dp[mxn][2];
vector<int> g[mxn];
vector<pi> v[mxn];
int ans[mxn];

void dfs(int c, int p){
	ans[c] = c + 1;
	for(int i : g[c]){
		if(i == p) continue;
		dfs(i, c);
		dp[c][0] += dp[i][1];
		v[c].push_back({dp[i][0] - dp[i][1] + 2, i});
	}
	sort(v[c].begin(), v[c].end());
	dp[c][1] = v[c].empty() ? 0x3f3f3f3f: 2;
	for(int i = 0; i < v[c].size(); i++){
		if(i) v[c][i].f += v[c][i - 1].f;
		dp[c][1] = min(dp[c][1], v[c][i].f);
	}
	dp[c][1] += dp[c][0];
}

void dfs2(int c, int p, int x){
	int st = 0;
	if(x){
		for(; st < v[c].size(); st++){
			if(dp[c][1] == dp[c][0] + v[c][st].f){
				for(int i = 0; i <= st; i++){
					dfs2(v[c][i].s, c, 0);
					swap(ans[c], ans[v[c][i].s]);
				}
				break;
			}
		}
		if(st == v[c].size()){
			dfs2(v[c][st = 0].s, c, 1);
			swap(ans[c], ans[v[c][0].s]);
		}
		st++;
	}
	for(st; st < v[c].size(); st++) dfs2(v[c][st].s, c, 1);
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
	dfs2(0, -1, 1);
	
	cout << dp[0][1] << endl;
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}