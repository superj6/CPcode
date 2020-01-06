#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long inf = 1000000007;

const int maxn = 100000, maxm = 26;
int n, m, k;
string s;
long long minv[26];
long long sum[maxn][26];
long long dp[maxn];
long long g[maxm][maxm];

int main(){
	freopen("cowmbat.in", "r", stdin);
	freopen("cowmbat.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k >> s;
	
	for(int i = 0; i < m; i++)
	for(int j = 0; j < m; j++) cin >> g[i][j];
	
	for(int l = 0; l < m; l++)
	for(int i = 0; i < m; i++)
	for(int j = 0; j < m; j++){
		g[i][j] = min(g[i][j], g[i][l] + g[l][j]);
	}
	
	for(int i = 0; i < m; i++) minv[i] = inf;
	
	for(int i = 0; i < n; i++){
		dp[i] = inf;
		for(int j = 0; j < m; j++){
			sum[i][j] = g[s[i] - 'a'][j];
			if(i) sum[i][j] += sum[i - 1][j];
			
			if(i == k - 1) minv[j] = 0;
			if(i >= k) minv[j] = min(minv[j], dp[i - k] - sum[i - k][j]);
			dp[i] = min(dp[i], sum[i][j] + minv[j]);
		}
	}
	
	cout << dp[n - 1] << endl;

	return 0;
}