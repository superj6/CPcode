#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define sz(k) (k * sizeof(ll))

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mxn = 101;
int n, k;
ll a[mxn], d[mxn];
ll dp[mxn][mxn], dp2[mxn][mxn];
vector<pi> g[mxn];

void dfs2(int c){
	memset(dp2[c], inf, sz(k));
	dp2[c][0] = a[c] * d[c];
	for(pi i : g[c]){
		d[i.f] = d[c] + i.s;
		dfs2(i.f);
		for(int j = k - 1; ~j; j--){
			ll ret = inf;
			for(int l = 0; l <= j; l++){
				ret = min(ret, dp2[c][j - l] + dp2[i.f][l]);
			}
			dp2[c][j] = ret;
		}
	}
	for(int i = 0; i < k; i++) dp2[c][i] = min(dp2[c][i], dp[c][i]);
}

void dfs(int c){
	for(pi i : g[c]) dfs(i.f);
	d[c] = 0;
	memset(dp[c], inf, sz(k));
	dfs2(c);
	memcpy(dp[c] + 1, dp2[c], sz(k));
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	k++;
	
	for(int i = 1; i <= n; i++){
		int p, w;
		cin >> a[i] >> p >> w;
		g[p].push_back({i, w});
	}
	
	dfs(0);
	
	cout << dp[0][k] << endl;

	return 0;
}