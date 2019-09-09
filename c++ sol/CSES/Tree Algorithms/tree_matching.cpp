#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n;
int dp[maxn][2];
vector<int> graph[maxn];

void dfs(int c, int p){
	int ret = maxn;
	for(int i : graph[c]){
		if(i == p) continue;
		dfs(i, c);
		dp[c][0] += dp[i][1];
		ret = min(ret, dp[i][1] - dp[i][0]);
	}
	dp[c][1] = max(dp[c][0], dp[c][0] - ret + 1);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	dfs(0, -1);
	
	cout << dp[0][1] << endl;

	return 0;
}