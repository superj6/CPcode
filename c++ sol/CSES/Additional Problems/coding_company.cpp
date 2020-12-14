#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007;
const int maxn = 101, maxm = 5001;
int n, m;
int a[maxn];
int dp[maxn][maxm];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a, a + n + 1);
	
	dp[0][0] = 1;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		for(int j = 1; j <= i; j++)
		for(int l = 0; l + a[i] - a[j] <= m; l++){
			dp[i][l + a[i] - a[j]] += dp[j - 1][l];
			dp[i][l + a[i] - a[j]] %= mod;
		}
	}
	
	int ret = 0;
	for(int i = 0; i <= m; i++) ret = (ret + dp[n][i]) % mod;
	
	cout << ret << endl;

	return 0;
}