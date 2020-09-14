/*
  Realize you just have to count the number of paths that go through each edge then test what each edge's cost is seperately based
on the number of paths going through it. To count the number of paths, I just take the subtree sum where each path has 1 added to
the node value at endpoints and 2 subtracted from node value of the path's lca to make sure not to count the path above subtree it is
contained within. I find all lca's using Tarjan's offline algorithm and take the subtree sums and total cost in 1 dfs.
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
