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

const int mxn = 200000;
int n;
ll u[mxn], v[mxn], w[mxn], z[mxn];
int vis[mxn], par[mxn], rnk[mxn], p[mxn], dp[mxn];
vector<int> g[mxn];

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

ll dfs(int c){
	ll ret = 0;
	vis[c] = 1, p[c] = par[c] = c, dp[c] = 1 + (c && c < n - 1);
	
	for(int i = c - 1; i <= c + 1; i += 2){
		if(i >= 0 && i < n && vis[i]) dp[p[fnd(i)]] -= 2;
	}
	
	for(int i : g[c]) if(!vis[c ^ u[i] ^ v[i]]){
		if(u[i] != c) swap(u[i], v[i]);
		ret += dfs(v[i]);
		
		dp[c] += dp[v[i]];
		ret += min(w[i] * dp[v[i]], z[i]);
		
		int x = fnd(c), y = fnd(v[i]);
		if(rnk[x] < rnk[y]) swap(x, y);
		rnk[x] += rnk[x] == rnk[y];
		par[y] = x, p[x] = c;
	}
	
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		cin >> u[i] >> v[i] >> w[i] >> z[i];
		g[--u[i]].push_back(i);
		g[--v[i]].push_back(i);
	}
	
	cout << dfs(0) << endl;

	return 0;
}