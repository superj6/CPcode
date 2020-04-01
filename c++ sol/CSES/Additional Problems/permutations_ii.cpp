#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007;
const int maxn = 1001;
int n;
long long dp[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	dp[0] = dp[1] = 1;
	dp[2] = dp[3] = 0;
	for(int i = 4; i <= n; i++){
		dp[i] += (i + 1) * dp[i - 1] % mod;
		dp[i] += mod - (i - 2) * dp[i - 2] % mod;
		dp[i] += mod - (i - 5) * dp[i - 3] % mod;
		dp[i] += (i - 3) * dp[i - 4] % mod;
		dp[i] %= mod;
	}
	
	cout << dp[n] << endl;

	return 0;
}