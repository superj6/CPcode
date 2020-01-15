#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 15;
int n, k;
int a[maxn][maxn];
int dp[maxn][maxn], dp2[maxn][maxn];

int solve(int x){
	int m = min(n - 1, k - __builtin_popcount(x));
	x |= (1 << (n - 1));
	
	for(int j = 0; j < n; j++)
	for(int l = 0; l <= j; l++){
		dp2[l][j] = 0;
		for(int i = 0, c = 0; i < n; i++){
			c += a[i][j] - (l ? a[i][l - 1] : 0);
			if(x & (1 << i)){
				dp2[l][j] = max(dp2[l][j], c);
				c = 0;
			}
		}
		if(!l) dp[0][j] = dp2[l][j];
	}
	
	for(int i = 1; i <= m; i++)
	for(int j = 0; j < n; j++){
		dp[i][j] = dp[i - 1][j];
		for(int l = 0; l <= j; l++){
			dp[i][j] = min(dp[i][j], max(dp2[l][j], (l ? dp[i - 1][l - 1] : 0)));
		}
	}
	
	return dp[m][n - 1];
}

int main(){
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		cin >> a[i][j];
		if(j) a[i][j] += a[i][j - 1];
	}
	
	int ret = 1000000007;
	for(int i = 0; i < (1 << (n - 1)); i++) if(__builtin_popcount(i) <= k) ret = min(ret, solve(i));
	
	cout << ret << endl;

	return 0;
}