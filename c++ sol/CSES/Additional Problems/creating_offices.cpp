#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 200000;
int n, m;
pi dp[maxn];
vector<int> graph[maxn];
vector<int> ans;
 
void dfs(int c, int p){
	if(graph[c].size() == (p != -1)){
		dp[c] = {1, 1};
		return;
	}
	int f = graph[c][0] == p;
	dfs(graph[c][f], c);
	dp[c] = dp[graph[c][f]];
	if(dp[c].s == m) dp[c].f++, dp[c].s = 0;
	for(int i = f + 1; i < graph[c].size(); i++){
		int v = graph[c][i];
		if(v == p) continue;
		dfs(v, c);
		if(dp[c].s + dp[v].s >= m) dp[c].f += dp[v].f, dp[c].s = min(dp[c].s, dp[v].s);
		else dp[c].f += dp[v].f - 1, dp[c].s = max(dp[c].s, dp[v].s);
	}
  	dp[c].s++;
}

void dfs2(int c, int p){
	if(dp[c].s == 1) ans.push_back(c + 1);
	bool t = 0;
	for(int i : graph[c]){
		if(i == p) continue;
		if(!t && dp[i].s % m == dp[c].s - 1){
			t = 1;
			dfs2(i, c);
		}else{
			dp[i].s = max(dp[i].s, m - dp[c].s + 1);
			dfs2(i, c);
		}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(0, -1);
	dfs2(0, -1);
	
	cout << dp[0].f << endl;
	cout << ans[0];
	for(int i = 1; i < dp[0].f; i++) cout << " " << ans[i];
	cout << endl;
 
	return 0;
}