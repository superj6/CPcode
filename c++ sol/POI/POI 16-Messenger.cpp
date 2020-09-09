/*
  Because you can query every possible combination in one round, you might as well precompute all ahead of time, as this is faster.
I essentially do dp where i start out with easily computing all paths of length t from i to all other nodes j, making sure i is
not used in cycle, then subtracting out paths with at least one cycle with j that doesn't include i. The states are:

f[t][i][j] = all paths length t from i to j with i only used at start
ff[t][i][j] = all cycles length t that use i only for start and end and don't touch j
fs[t][i][j] = combinations of multiple cycles that start and end at i and don't touch j
dp[t][i][j] = number of paths from i to j that only use i at start and j at end
s[t][i][j] = number of combinations of dp[l][i][j] * fs[t - l][j][i], used to cut factor from transitions

Our end goal is to compute dp[t][i][j] = f[t][i][j] - sum of f[l][i][j] * ff[t - l][j][i], because we want to subtract each invalid
path which will definitely have at least one cycle at the end, and can have any path to j with or without cycles before that. Only
multiplying by a single final cycle makes sure we don't overcount.

We can count ff[t][i][j] by counting f[t][i][i] - sum of all cycles that use j at least once. All cycles that use i at least once will
be in the form of dp[p][i][j] * fs[p - l][j][i] * dp[t - l][j][i], because this will make sure we only go from i to j back to i without
only using i and j once in cycle, but we can also use many cycles with j that don't include i in between those paths. We can compute fs
easily with transition fs[t][i][j] = sum of fs[l][i][j] * ff[t - l][i][j] because we can use many cycles before but each combination will
have at least one final cycle at the end. Finally, to cut out a factor of k from time complexity, just store s[i][j] = sum of all 
dp[l][i][j] * fs[t - l][j][i] so you can do transitions of cycles using j at least once as s[l][i][j] * dp[t - l][j][i].

This leaves a total time complexity of O(n^2 * k * (n + k)), or since n is approximately k, O(n ^ 4), which is plenty fast enough,
and we just output queries in O(1).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100, k = 51;
int n, m, q, mod;
int g[mxn][mxn];
ll f[k][mxn][mxn], ff[k][mxn][mxn], fs[k][mxn][mxn], dp[k][mxn][mxn], s[k][mxn][mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> mod;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		g[--u][--v]++;
	}
	
	for(int i = 0; i < n; i++) f[0][i][i] = dp[0][i][i] = 1;
	
	for(int t = 1; t < k; t++){
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		for(int l = 0; l < n; l++){
			if(!~-t || i != l) (f[t][i][j] += f[t - 1][i][l] * g[l][j]) %= mod;
		}
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			for(int l = 1; l < t; l++){
				(ff[t][i][j] += s[l][i][j] * dp[t - l][j][i]) %= mod;
				(fs[t][i][j] += fs[l][i][j] * ff[t - l][i][j]) %= mod;
				(dp[t][i][j] += f[l][i][j] * ff[t - l][j][i]) %= mod;
				(s[t][i][j] += dp[l][i][j] * fs[t - l][j][i]) %= mod;
			}
			ff[t][i][j] = (mod + f[t][i][i] - ff[t][i][j]) % mod;
			(fs[t][i][j] += ff[t][i][j]) %= mod;
			dp[t][i][j] = (mod + f[t][i][j] - dp[t][i][j]) % mod;
			(s[t][i][j] += dp[t][i][j]) %= mod;
		}
	}
	
	cin >> q;
	
	while(q--){
		int x, y, t;
		cin >> x >> y >> t;
		cout << dp[t][--x][--y] << endl;
	}

	return 0;
}
