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

const int mxn = 2000000;
int n;
int a[mxn];
int dp[mxn][2];
vector<int> g[mxn];

void dfs(int c, int p){
	int mx[2] = {0, -1};
	for(int i : g[c]){
		if(i == p) continue;
		dfs(i, c);
		dp[c][0] += max(dp[i][0], dp[i][1] - 1);
		for(int j = 0; j < 2; j++){
			mx[j] = max(mx[j], dp[i][j]);
		} 
	}
	if(a[c]){
		dp[c][0] = max(dp[c][0] - 1, 1);	
		dp[c][1] = max(mx[0], mx[1] - 1);
	}else{
		dp[c][1] = mx[1];
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	for(int i = 0; i < n; i++){
		char c;
		cin >> c;
		a[i] = c & 1;
	}
	
	dfs(0, -1);
	
	cout << max(dp[0][0], dp[0][1] + 1) << endl;

	return 0;
}