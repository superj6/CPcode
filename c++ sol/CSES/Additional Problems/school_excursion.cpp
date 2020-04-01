#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100001;
int n, m;
int a[maxn], b[maxn];
bool used[maxn], dp[maxn];
vector<int> graph[maxn];

int dfs(int c){
	used[c] = 1;
	int ret = 1;
	for(int i : graph[c]){
		if(used[i]) continue;
		ret += dfs(i);
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	for(int i = 0; i < n; i++) if(!used[i]) a[dfs(i)]++;
	
	dp[0] = 1;
	for(int i = 1; i <= n; i++) if(a[i]){
		for(int j = 0; j < i; j++) b[j] = n + 1;
		for(int j = n; j >= 0; j--) if(dp[j]){
			for(int k = 1; k <= a[i] && j + i * k < b[j % i]; k++) dp[j + i * k] = 1;
			b[j % i] = j;
		}
	}
	
	for(int i = 1; i <= n; i++) cout << dp[i];
	cout << endl;

	return 0;
}