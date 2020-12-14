#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 17;
int n, m, k, x, y;
int a[mxn], b[mxn];
int g[mxn][mxn];
int dp[1 << mxn][mxn][mxn];

void answer(){
	cin >> k >> x >> y >> n >> m;
	
	for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
	
	memset(g, 0x3f, sizeof(g));
	for(int i = 0; i < m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		g[u][v] = min(g[u][v], w);
		g[v][u] = min(g[v][u], w);
	}
	
	int ret = -1;
	memset(dp, 0x3f, sizeof(dp));
	dp[1][0][0] = 0;
	for(int i = 0; i < (1 << (n + 1)); i++)
	for(int p = 0; p <= n; p++){
		for(int j = 0; j <= n; j++){
			int dpc = dp[i][j][p];
			for(int l = 0; l <= n + 1; l++) if(!(i & (1 << l))){
				int &dpn = dp[i | (1 << l)][l][p];
				dpn = min(dpn, dpc + g[j][l]);
				
				int &dpn2 = dp[i | (1 << l)][l][p + a[l] + b[l]];
				dpn2 = min(dpn2, dpc + g[j][l] + x * a[l] + y * b[l]);
			}
		}
		if(dp[i | (1 << (n + 1))][n + 1][p] <= k) ret = max(ret, p);
	}
	
	if(!~ret) cout << "Book a flight!" << endl;
	else cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}