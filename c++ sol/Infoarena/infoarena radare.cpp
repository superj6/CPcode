/*
  The naive dp is to hold dp[node][sum], and use a knapsack like dp to add subtrees resulting in O(nk^2). To speed this up, you can
reindex the nodes and compute dp transitions in the euler tour order. When transitioning, if you decide to cutoff the subtree the node
is located in, you add dp[node][sum] * pow(2, node subtree size - 1) to dp[next node outside subtree][sum], because you won't add the
sum of any nodes inside the subtree but you can pick any combination of edges within the subtree. However if you don't cutoff the
subtree of the node, you add dp[node][sum] to dp[next node][sum + node value], because you may still add the value of any node next
even if it's in the subtree, but you're adding the nodes value to the sum since it must be reachable because you did not block it.
Because there are only two transitions per state, this is O(nk).
*/

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

const int mod = 31333;
const int mxn = 3501;
int n, k;
int a[mxn], b[mxn], l[mxn], r[mxn], id[mxn];
int dp[mxn][mxn];
vector<int> g[mxn];

int dfs(int c, int p){
	id[r[c] = l[c]] = c;
	for(int i : g[c]){
		if(i == p) continue;
		l[i] = r[c] + 1;
		r[c] = dfs(i, c);
	}
	return r[c];
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
	
	b[0] = 1;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		b[i + 1] = 2 * b[i] % mod;
	}
	
	dfs(0, -1);
	
	dp[0][0] = 1;
	for(int i = 0; i < n; i++)
	for(int j = 0; j <= k; j++){
		if(!dp[i][j]) continue;
		int x = id[i];
		(dp[r[x] + 1][j] += dp[i][j] * b[r[x] - l[x]]) %= mod;
		if(j + a[x] <= k) (dp[i + 1][j + a[x]] += dp[i][j]) %= mod;
	}
	
	cout << dp[n][k] << endl;

	return 0;
}
