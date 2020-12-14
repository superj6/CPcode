//VwzqYy37
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000000;
int n;
int a[maxn][2];
int dp[maxn][2][2];

bool rng(int x, int y, int z){
	return dp[x][y][0] <= z && z <= dp[x][y][1];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int j = 0; j < 2; j++)
	for(int i = 0; i < 2 * n; i++) cin >> a[i][j];
	
	dp[0][0][0] = dp[0][0][1] = 0;
	dp[0][1][0] = dp[0][1][1] = 1;
	for(int i = 1; i < 2 * n; i++){
		dp[i][0][0] = dp[i][1][0] = 3 * n;
		dp[i][0][1] = dp[i][1][1] = -3 * n;
		for(int j = 0; j < 2; j++)
		for(int k = 0; k < 2; k++){
			if(a[i - 1][j] <= a[i][k] && dp[i - 1][j][0] <= dp[i - 1][j][1]){
				dp[i][k][0] = min(dp[i][k][0], dp[i - 1][j][0] + k);
				dp[i][k][1] = max(dp[i][k][1], dp[i - 1][j][1] + k);
			}
		}
	}
	
	if(!rng(2 * n - 1, 0, n) && !rng(2 * n - 1, 1, n)){
		cout << -1 << endl;
		return 0;
	}
	
	string ret;
	for(int i = 2 * n - 1, j = n; i >= 0; i--){
		if(!rng(i, 0, j)){
			ret += 'B';
			j--;
		}else if(!rng(i, 1, j)){
			ret += 'A';
		}else if(a[i][1] < a[i][0]){
			ret += 'B';
			j--;
		}else{
			ret += 'A';
		}
	}
	reverse(ret.begin(), ret.end());
	
	cout << ret << endl;

	return 0;
}