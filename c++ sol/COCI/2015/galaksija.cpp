#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
int n;
int u[mxn], v[mxn], w[mxn];
int qr[mxn], par[mxn], s[mxn];
map<int, int> dp[mxn];
vector<int> g[mxn];
ll ans[mxn];

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

void dfs(int c, int p){
	par[c] = c, dp[c][s[c]] = 1;
	for(int i : g[c]){
		if(i == p) continue;
		int j = c ^ u[i] ^ v[i];
		s[j] = s[c] ^ w[i];
		dfs(j, i);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i < n; i++){
		cin >> u[i] >> v[i] >> w[i];
		g[--u[i]].push_back(i);
		g[--v[i]].push_back(i);
	}
	
	dfs(0, -1);
	
	for(int i = 1; i < n; i++) cin >> qr[i];
	
	reverse(qr + 1, qr + n);
	
	for(int i = 1; i < n; i++){
		ans[i] = ans[i - 1];
		int x = fnd(u[qr[i]]), y = fnd(v[qr[i]]);
		if(dp[x].size() < dp[y].size()) swap(x, y);
		for(pi j : dp[y]){
			ans[i] += (ll)j.s * dp[x][j.f];
			dp[x][j.f] += j.s;
		}
		dp[y].clear();
		par[y] = x;
	}
	
	reverse(ans, ans + n);
	
	for(int i = 0; i < n; i++) cout << ans[i] << endl;

	return 0;
}