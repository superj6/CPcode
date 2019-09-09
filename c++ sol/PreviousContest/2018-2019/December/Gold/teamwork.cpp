#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'

int maxq[10000][14];

int getmax(int l, int r){
	int j = log2(r - l + 1);
	return max(maxq[l][j], maxq[r - (1 << j) + 1][j]);
}

int main(){
	freopen("teamwork.in", "r", stdin);
	freopen("teamwork.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	for(int i = 0; i < n; i++) cin >> maxq[i][0];
	
	for(int j = 1; j <= log2(n); j++){
		for(int i = 0; i + (1 << j) <= n; i++){
			maxq[i][j] = max(maxq[i][j - 1], maxq[i + (1 << (j - 1))][j - 1]);
		}
	}
	
	int dp[n + 1];
	dp[0] = 0;
	
	for(int i = 1; i <= n; i++){
		dp[i] = 0;
		for(int j = 0; j < k && i - j - 1 >= 0; j++){
			dp[i] = max(dp[i], dp[i - j - 1] + getmax(i - j - 1, i - 1) * (j + 1));
		}
	}
	
	cout << dp[n] << endl;

	return 0;
}