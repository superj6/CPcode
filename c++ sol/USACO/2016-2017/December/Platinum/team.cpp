#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int mod = 1000000009;

int main(){
	freopen("team.in", "r", stdin);
	freopen("team.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	int a[n], b[m];
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < m; i++) cin >> b[i];
	
	int dp[n][m][k];
	
	for(int l = 0; l < k; l++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				dp[i][j][l] = 0;
				
				if(a[i] > b[j]){
					if(l > 0){
						if(i > 0 && j > 0) dp[i][j][l] = dp[i - 1][j - 1][l - 1];
					} else dp[i][j][l] = 1;
					
				}
				
				if(i > 0) dp[i][j][l] += dp[i - 1][j][l];
				dp[i][j][l] %= mod;
				if(j > 0) dp[i][j][l] += dp[i][j - 1][l];
				dp[i][j][l] %= mod;
				if(i > 0 && j > 0) dp[i][j][l] -= dp[i - 1][j - 1][l];
				dp[i][j][l] = (dp[i][j][l] + mod) % mod;
			}
		}
	}
	
	cout << dp[n - 1][m - 1][k - 1] << endl;

	return 0;
}