#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int inf = 1000000007;
const int maxn = 1000;
int n, m, c;
int a[maxn], dp[maxn], dp2[maxn];
vector<int> graph[maxn];

int main(){
	freopen("time.in", "r", stdin);
	freopen("time.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> c;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		dp2[i] = -inf;
	}
	dp2[0] = 0;
	
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		graph[y].push_back(x);
	}
	
	int ret = 0;
	for(int t = 1; t < maxn; t++){
		for(int i = 0; i < n; i++){
			dp[i] = -inf;
			for(int j : graph[i]) dp[i] = max(dp[i], dp2[j]);
			if(dp[i] != -inf) dp[i] += a[i];
		}
		ret = max(ret, dp[0] - c * t * t);
		memcpy(dp2, dp, sizeof(dp));
	}
	
	cout << ret << endl;

	return 0;
}