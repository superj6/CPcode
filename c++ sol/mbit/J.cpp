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

const int mxn = 5001;
int n;
int a[mxn], sz[mxn], f[mxn];
int dp1[mxn][mxn], dp2[mxn][mxn];
vector<int> g[mxn];

void dfs(int c, int p){
	dp1[c][1] = dp2[c][a[c]] = 0, sz[c] = 1;
	for(int i : g[c]) if(i != p){
		dfs(i, c);
		
		int x = 0; // parent edge pointing up
		for(int j = 0; j <= sz[i]; j++) x = max(x, dp2[i][j] + j);
		for(int j = 0; j <= sz[c] + sz[i]; j++) f[j] = dp1[c][j] + x;
		for(int j = 0; j <= sz[c]; j++)
		for(int l = 0; l <= sz[i]; l++){
			f[j + l] = max(f[j + l], dp1[c][j] + dp1[i][l] + l * a[c]);
		}
		memcpy(dp1[c], f, (sz[c] + sz[i] + 1) * sizeof(int));
		
		x = 0; // parent edge pointing down
		for(int j = 0; j <= sz[i]; j++) x = max(x, dp1[i][j] + j * a[c]);
		for(int j = 0; j <= sz[c] + sz[i]; j++) f[j] = dp2[c][j] + x;
		for(int j = 0; j <= sz[c]; j++)
		for(int l = 0; l <= sz[i]; l++){
			f[j + l] = max(f[j + l], dp2[c][j] + dp2[i][l] + l);
		}
		memcpy(dp2[c], f, (sz[c] + sz[i] + 1) * sizeof(int));
		
		sz[c] += sz[i];
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		char c;
		cin >> c;
		a[i] = c & 1;
	}
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	memset(dp1, 0xcf, sizeof(dp1));
	memset(dp2, 0xcf, sizeof(dp2));
	
	dfs(0, -1);
	
	int ret = max(
		*max_element(dp1[0], dp1[0] + n + 1), 
		*max_element(dp2[0], dp2[0] + n + 1)
	);
	
	cout << ret << endl;

	return 0;
}