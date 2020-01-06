/*
	This is a very simple dynamic programming problem. Because n and k are small, you can suffice with an O(n * k) solution,
where you hold dp[i] which has the max sum of skills levels up to cow i. You can then iterate through each i from 1 to n and
at each i iterate backwards k spaces backwards while continuously holding the maxmimum element encountered, and set dp[i] as the
max value of dp[j] + mx * (i - j), where j is the previous index and mx is the max element encountered. I was stupid and instead
used a sparse table rather than iterate backwards lol.
*/

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
