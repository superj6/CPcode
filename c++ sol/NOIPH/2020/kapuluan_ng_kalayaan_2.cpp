#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 1000000;
int n, m, k;
int a[mxn], it[mxn];
int u[mxn], v[mxn], w[mxn];
int par[mxn], sz[mxn];

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) par[i] = i, sz[i] = 1;
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i] >> w[i];
		u[i]--, v[i]--;
		it[i] = i;
	}
	u[m] = v[m] = 0, w[m] = 2 * mod, it[m] = m, m++;
	for(int i = 0; i < k; i++) cin >> a[i];
	
	sort(it, it + m, [&](int x, int y){
		return w[x] < w[y];
	});
	sort(a, a + k);
	
	ll ret = 1, r = (ll)n * (n - 1) % mod * (mod + 1) % mod;
	for(int i = 0, j = 0; i < m; i++){
		for(; j < k && a[j] < w[it[i]]; j++) (ret *= r) %= mod;
		int x = fnd(u[it[i]]), y = fnd(v[it[i]]);
		if(x != y){
			(r += mod - 2 * sz[x] * sz[y]) %= mod;
			if(sz[x] < sz[y]) swap(x, y);
			par[y] = x, sz[x] += sz[y];
		}
	}
	
	cout << ret << endl;

	return 0;
}