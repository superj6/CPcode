	
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int mod = 200003;
const int mxn = 1001;
int n;
ll dp[mxn];
ll f[mxn][mxn];
 
int main(){
	freopen("matcnt.in", "r", stdin);
	freopen("matcnt.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i <= n; i++){
		f[i][0] = 1;
		for(int j = 1; j <= i; j++) f[i][j] = (i - j + 1) * f[i][j - 1] % mod;
	}
	
	dp[0] = 1;
	for(int i = 3; i <= n; i++){
		dp[i] = 1;
		for(int j = i; j > 2; j--){
			(dp[i] += f[i - 1][j - 1] * f[i][j] % mod * (mod + 1) / 2 % mod * dp[i - j]) %= mod;
		}
		(dp[i] += mod - 1) %= mod;
	}
	
	cout << dp[n] << endl;
 
	return 0;
}