#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long mod = 1000000007;
 
long long modpow(long long b, int e){
	long long ret = 1;
	for(int i = 0; (1 << i) <= e; i++){
		if((1 << i) & e) ret = (ret * b) % mod;
		b = (b * b) % mod;
	}
	return ret;
}

const int maxn = 2002;
int n;
int a[maxn][maxn];
long long dp[maxn][maxn][2];
int inv2 = modpow(2, mod - 2);
int s;

int main(){
	freopen("sprinklers2.in", "r", stdin);
	freopen("sprinklers2.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		a[i][j] = c == '.';
		s += a[i][j];
	}
	
	dp[0][1][0] = dp[1][0][1] = 1;
	for(int i = 0; i <= n; i++)
	for(int j = 0; j <= n; j++){
		dp[i][j + 1][0] += dp[i][j][0];
		dp[i][j + 1][0] %= mod;
		dp[i + 1][j][1] += dp[i][j][1];
		dp[i + 1][j][1] %= mod;
		if(j && a[i][j - 1]){
			dp[i + 1][j][1] += dp[i][j][0] * inv2 % mod;
			dp[i + 1][j][1] %= mod;
		}
		if(i && a[i - 1][j]){
			dp[i][j + 1][0] += dp[i][j][1] * inv2 % mod;
			dp[i][j + 1][0] %= mod;
		}
	}
	
	cout << ((dp[n][n][0] + dp[n][n][1]) % mod * modpow(2, s) % mod) << endl;

	return 0;
}