#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long mod = 1000000007;
const int maxn = 3004;
int n, m;
long long dp[maxn][maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	n += 4, m += 4;
	
	for(long long i = 4; i < n; i++){
		for(long long j = 4; j < m; j++){
			dp[i][j] += 4 * (dp[i - 1][j - 1] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += (j - 4) * (dp[i - 1][j - 2] + 1) % mod + (i - 4) * (dp[i - 2][j - 1] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += 16 * (i - 4) * (j - 4) % mod * (dp[i - 2][j - 2] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += 6 * (i - 4) * (i - 5) * (j - 4) % mod * (dp[i - 3][j - 2] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += 6 * (i - 4) * (j - 4) * (j - 5) % mod * (dp[i - 2][j - 3] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += 5 * (i - 4) * (i - 5) * (j - 4) * (j - 5) / 4 % mod * (dp[i - 3][j - 3] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += (i - 4) * (i - 5) * (i - 6) * (j - 4) / 2 % mod * (dp[i - 4][j - 2] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += (i - 4) * (j - 4) * (j - 5) * (j - 6) / 2 % mod * (dp[i - 2][j - 4] + 1) % mod;
			dp[i][j] %= mod;
			
			dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mod;
			dp[i][j] %= mod;
			
			//cout << (i - 2) << " " << (j - 2) << ": " << dp[i][j] << endl;
		}
	}
	
	cout << dp[n - 1][m - 1] << endl;

	return 0;
}