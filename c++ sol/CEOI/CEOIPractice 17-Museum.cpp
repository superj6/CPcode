/*
  Realize all vertices in best group connected and a single path from the root will have edges count once, and all other edges will
be counted twice. Use knapsack dp to combine subtrees and make sure the bound on the knapsack never loops over unnecessary indices,
as it can then be proved the algorithm runs in O(n^2) as shown on the 25th page of "Looking for a Challenge", located here:
http://www.lookingforachallengethebook.com/uploads/1/4/5/5/14555448/preview-_looking_for_a_challenge.pdf.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int inf = 0x3f3f3f3f;
const int mxn = 10001;
int n, k, x;
int sz[mxn];
int dp[mxn][mxn][2];
vector<pi> g[mxn];
 
void dfs(int c, int p){
	sz[c] = 1;
	memset(dp[c], inf, sizeof(dp[c]));
	dp[c][1][0] = dp[c][1][1] = 0;
	for(pi i : g[c]){
		if(i.f == p) continue;
		dfs(i.f, c);
		for(int j = min(k, sz[c] + sz[i.f]); j; j--){
			int ret[2] = {inf, inf};
			for(int l = max(1, j - sz[c]); l <= min(j, sz[i.f]); l++)
			for(int p1 = 0; p1 < 2; p1++)
			for(int p2 = 0; p2 < 2 - p1; p2++){
				ret[p1 | p2] = min(ret[p1 | p2], dp[c][j - l][p1] + dp[i.f][l][p2] + (1 + !p2) * i.s); 
			}
			for(int l = 0; l < 2; l++){
				dp[c][j][l] = min(dp[c][j][l], ret[l]);
			}
		}
		sz[c] += sz[i.f];
	}
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> x;
	x--;
	
	for(int i = 0; i < n - 1; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	dfs(x, -1);
	
	cout << dp[x][k][1] << endl;
 
	return 0;
}
