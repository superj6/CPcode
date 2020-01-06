#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 300;
int n, m;
int dp[maxn][maxn];
int dp2[maxn][maxn][maxn];

int main(){
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int w, l, r;
		cin >> w >> l >> r;
		l--, r--;
		
		for(int j = l; j <= r; j++){
			dp2[l][j][r] = max(dp2[l][j][r], w);
		}
	}
	
	for(int j = 0; j < n; j++)
	for(int i = j; i >= 0; i--)
	for(int k = j; k < n; k++){
		if(i) dp2[i - 1][j][k] = max(dp2[i - 1][j][k], dp2[i][j][k]);
		if(k < n - 1) dp2[i][j][k + 1] = max(dp2[i][j][k + 1], dp2[i][j][k]);
	}
	
	for(int i = n - 1; i >= 0; i--)
	for(int k = i; k < n; k++)
	for(int j = i; j <= k; j++){
		if(j < k) dp[i][k] = max(dp[i][k], dp[i][j] + dp[j + 1][k]);
		dp[i][k] = max(dp[i][k], (j > i ? dp[i][j - 1] : 0) + dp2[i][j][k] + (j < k ? dp[j + 1][k] : 0));
	}
	
	
	cout << dp[0][n - 1] << endl;
}