#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

long mod = 1000000007;

int main(){
	freopen("palpath.in", "r", stdin);
	freopen("palpath.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	char grid[n][n];
	
	for(int i = 0; i < n; i++) cin >> grid[i];
	
	long dp[n][n];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j) dp[i][j] = 1;
			else dp[i][j] = 0;
		}
	}
	
	for(int num = n - 1; num >= 1; num--){
		long next[n][n];
		memset(next, 0, sizeof(next));
		
		for(int a = 0; a < n; a++){
			int rowA = a;
			int colA = num - 1 - a;
			if(colA < 0) continue;
			
			for(int b = 0; b < n; b++){
				int rowB = b;
				int colB = 2 * n - num - 1 - b;
				if(colB >= n) continue;
				if(grid[rowA][colA] != grid[rowB][colB]) continue;
				next[rowA][rowB] += dp[rowA][rowB];
				if(rowA + 1 < n) next[rowA][rowB] += dp[rowA + 1][rowB];
				if(rowB - 1 >= 0) next[rowA][rowB] += dp[rowA][rowB - 1];
				if(rowA + 1 < n && rowB - 1 >= 0) next[rowA][rowB] += dp[rowA + 1][rowB - 1];
				next[rowA][rowB] %= mod;
			}
		}
		copy(&next[0][0], &next[0][0] + n * n, &dp[0][0]);
	}
	
	cout << dp[0][n - 1] << endl;

	return 0;
}