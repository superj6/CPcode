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

const int mod = 1000000007;
const int mxn = 100000;
ll n, k;
int f[mxn], f2[mxn], dp[mxn], dp2[mxn][2];
ll ff[2], ff2[2];
vector<int> g[mxn];

void add(int x, int y, int z){
	dp[x] += z * !dp[y];
	dp2[x][!!dp[y]] += z * (!dp[y] + (dp[y] <= 1) * dp2[y][!dp[y]]);
}

void dfs(int c, int p){
	for(int i : g[c]) if(i != p) dfs(i, c), add(c, i, 1);
}

void dfs2(int c, int p){
	f[c] = !!dp[c], f2[c] = !dp[c] + (dp[c] <= 1) * dp2[c][!dp[c]];
	ff[f[c]]++, (ff2[f[c]] += f2[c]) %= mod;
	for(int i : g[c]) if(i != p){
		add(c, i, -1), add(i, c, 1);
		dfs2(i, c);
		add(i, c, -1), add(c, i, 1);
	}
}

ll ipow(ll x, ll y){
	ll ret = 1;
	for(; y; y >>= 1){
		if(y & 1) (ret *= x) %= mod;
		(x *= x) %= mod;
	}
	return ret;
}

int main(){
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
	
	dfs(0, -1);
	dfs2(0, -1);
	
	ll x = ipow(n, 2 * k), y = (mod + ff2[1] - ff2[0]) % mod;
	ll dpf = ff[0] * (mod + x - ipow(y, k)) % mod * ipow(mod + ipow(n, 2) - y, mod - 2) % mod;
	
	ll ret = (f[0] ? mod + x - f2[0] * dpf % mod : f2[0] * dpf) % mod;
	
	cout << ret << endl;

	return 0;
}