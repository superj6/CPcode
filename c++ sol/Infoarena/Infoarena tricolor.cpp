/*
  Hold dp[vertex][number of connected white vertices] for case of the current vertex is black, and dp2[vertex] for case of the current
vertex is white. Now you can just transition by multiplying number of connected white vertices in current node and current subtree, and
make sure you do it in O(n^2) by using the combining subtrees trick of only iterating over necessary states.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 5000;
int n;
int sz[mxn];
ll dp[mxn][mxn], dp2[mxn];
vector<int> g[mxn];

void dfs(int c, int p){
	memset(dp[c], 0xcf, sizeof(dp[c]));
	sz[c] = 1, dp[c][0] = dp2[c] = 0;
	for(int i : g[c]){
		if(i == p) continue;
		dfs(i, c);
		
		for(int j = sz[c] + sz[i] - 1; j; j--){
			ll ret = dp[c][j - 1] + dp2[i] + j - 1;
			for(int l = max(1, j - sz[c]); l <= min(j, sz[i]); l++){
				ret = max(ret, dp[c][j - l] + dp[i][l] + (ll)l * (j - l));
			}
			dp[c][j] = ret;
		}
		
		ll ret = dp2[i] + 1;
		for(int j = 1; j < sz[i]; j++) ret = max(ret, j + dp[i][j]);
		dp2[c] += ret;
		
		sz[c] += sz[i];
	}
}

void answer(){
	cin >> n;
	
	for(int i = 0; i < n; i++) g[i].clear();
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(0, -1);
	
	cout << max(*max_element(dp[0], dp[0] + n), dp2[0]) << endl;
}

int main(){
	freopen("tricolor.in", "r", stdin);
	freopen("tricolor.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();
	
	return 0;
}
