#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>

const int maxn = 100000, maxm = 101;
int n, m;
long long a[maxn], s[maxn];
pi t[maxm];
pi dp[maxn][maxm];
vector<int> graph[maxn];

long long dfs(int c, int p){
	long long ret = 0;
	dp[c][1].first = s[c];
	for(int i : graph[c]){
		if(i == p) continue;
		ret = max(ret, dfs(i, c));
		for(int j = 1; j <= m; j++){
			t[j].first = max(dp[i][j].first, dp[i][j - 1].first + s[c] - a[i]);
			t[j].second = max(dp[i][j].second, dp[i][j - 1].second + s[i] - a[c]);
			if(j != m){
				ret = max(ret, max(dp[c][m - j].first + t[j].second, dp[c][m - j].second + t[j].first));
				ret = max(ret, dp[i][j].second + s[c]);
			}
		}
		for(int j = 1; j <= m; j++){
			dp[c][j].first = max(dp[c][j].first, t[j].first);
			dp[c][j].second = max(dp[c][j].second, t[j].second);
			ret = max(ret, dp[c][j].first);
		}
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 0; i < n - 1; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		
		s[y] += a[x];
		s[x] += a[y];
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	cout << dfs(0, -1) << endl;

	return 0;
}