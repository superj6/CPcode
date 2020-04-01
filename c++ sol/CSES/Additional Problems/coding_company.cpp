#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007;
const int maxn = 101, maxm = 5001;
int n, m;
int a[maxn];
long long dp[maxn][maxm], dp2[maxn][maxm];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	dp[0][0] = dp[1][0] = 1;
	for(int i = 0; i < n - 1; i++){
		a[i] = a[i + 1] - a[i];
		memset(dp2, 0, sizeof(dp2));
		for(int k = 0; k < n; k++)
		for(int j = 0; j + k * a[i] <= m; j++){
			if(k) dp2[k - 1][j + k * a[i]] += k * dp[k][j] % mod;
			dp2[k][j + k * a[i]] += (k + 1) * dp[k][j] % mod;
			dp2[k + 1][j + k * a[i]] += dp[k][j] % mod;
			
			if(k) dp2[k - 1][j + k * a[i]] %= mod;
			dp2[k][j + k * a[i]] %= mod;
			dp2[k + 1][j + k * a[i]] %= mod;
		}
		memcpy(dp, dp2, sizeof(dp));
	}
	
	int ret = 0;
	for(int i = 0; i <= m; i++) ret = (ret + dp[0][i]) % mod;
	
	cout << ret << endl;

	return 0;
}