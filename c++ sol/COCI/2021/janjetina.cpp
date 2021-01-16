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
#define vi vector<pi>

void mrg(vi &x, vi &y){
	vi v(x.size() + y.size());
	merge(x.begin(), x.end(), y.begin(), y.end(), v.begin());
	swap(x, v);
}

const int mxn = 100001;
int n, k;
int d[mxn], dp[mxn], sz[mxn], vis[mxn], bit[mxn];
vi a, b;
vi g[mxn];

void add(int x, int v){
	for(x++; x < mxn; x += x & -x) bit[x] += v;
}

ll qry(int x){
	ll ret = 0;
	for(x++; x; x -= x & -x) ret += bit[x];
	return ret;
}

int dfsc(int c, int p){
	sz[c] = 1;
	for(pi i : g[c]) if(i.f != p && !vis[i.f]) sz[c] += dfsc(i.f, c);
	return sz[c];
}

int dfsc2(int c, int p){
	for(pi i : g[c]) if(i.f != p && !vis[i.f] && 2 * sz[i.f] > sz[c]){
		sz[c] -= sz[i.f], sz[i.f] += sz[c];
		return dfsc2(i.f, c);
	}
	return c;
}

void dfs(int c, int p){
	b.push_back({dp[c], d[c]});
	for(pi i : g[c]) if(i.f != p && !vis[i.f]){
		d[i.f] = d[c] + 1, dp[i.f] = max(dp[c], i.s);
		dfs(i.f, c);
	}
}

ll f(vi &v){
	ll ret = 0;
	for(pi i : v){
		if(i.f >= k + i.s) ret += qry(i.f - k - i.s);
		add(i.s, 1);
	}
	for(pi i : v) add(i.s, -1);
	return ret;
}

ll sol(int c){
	dfsc(c, -1);
	vis[c = dfsc2(c, -1)] = 1;
	
	ll ret = 0;
	a.assign(1, {dp[c] = 0, d[c] = 0});
	for(pi i : g[c]) if(!vis[i.f]){
		d[i.f] = d[c] + 1, dp[i.f] = max(dp[c], i.s);
		b.clear();
		dfs(i.f, c);
		
		sort(b.begin(), b.end());
		ret -= f(b);
		mrg(a, b);
	}
	ret += f(a);
	
	for(pi i : g[c]) if(!vis[i.f]) ret += sol(i.f);
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n - 1; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	cout << (2 * sol(0)) << endl;

	return 0;
}