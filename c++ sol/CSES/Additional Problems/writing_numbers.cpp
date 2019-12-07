#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int m = 19, k = 10;
long long n;
int a[m];
long long dp[m][m][k][2];

long long solve(long long x){
	for(int i = m - 1; i >= 0; i--, x /= 10) a[i] = x % 10;
	
	memset(dp, 0, sizeof(dp));
	dp[0][0][0][0] = 1;
	
	long long ret = 0;
	for(int i = 0; i < m; i++)
	for(int j = 0; j < m; j++)
	for(int l = 0; l < k; l++){
		if(i == m - 1){
			ret += j * (dp[i][j][l][0] + dp[i][j][l][1]);
		}else{
			for(int x = 0; x < k; x++){
				int c = x == 1;
				if(x < a[i + 1]) dp[i + 1][j + c][x][1] += dp[i][j][l][0];
				else if(x == a[i + 1]) dp[i + 1][j + c][x][0] += dp[i][j][l][0];
				dp[i + 1][j + c][x][1] += dp[i][j][l][1];
			}
		}
	}
	
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	long long l = 1, r = 1000000000000000000;
	while(r - l > 1){
		long long mid = (l + r) / 2;
		if(solve(mid) <= n) l = mid;
		else r = mid;
	}
	
	cout << l << endl;

	return 0;
}