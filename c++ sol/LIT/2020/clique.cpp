#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 21;
int n, m;
ll a[mxn], vis[mxn];
map<ll, ll, greater<ll>> dp;
vector<int> g[mxn];

void dfs(int c){
	vis[c] = 1;
	for(int i : g[c]) dfs(i);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		if(u < v) swap(u, v);
		g[--u].push_back(--v);
	}
	
	dfs(n - 1);
	
	ll ret = 1;
	for(int i = 1; i < n; i++){
		if(!vis[i]) continue;
		dp.clear();
		dp[0] = 1;
		sort(g[i].begin(), g[i].end());
		g[i].push_back(i);
		for(int j = 0; j < g[i].size() - 1; j++)
		for(pi k : dp)
		for(ll l = a[g[i][j]]; l <= a[i]; l += a[g[i][j]]){
			if((k.f + l) % a[g[i][j + 1]] == 0){
				(dp[k.f + l] += k.s) %= mod;
			}
		}
		(ret *= dp[a[i]]) %= mod;
	}
	
	cout << ret << endl;

	return 0;
}