#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	freopen("snakes.in", "r", stdin);
	freopen("snakes.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	int a[n];
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	int dp[n][k + 1];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= k; j++){
			
			if(i == 0){
				dp[i][j] = 0;
				continue;
			}
			
			int maxv = 0;
			int sumv = 0;
			dp[i][j] = 1000000007;
			
			for(int l = i; l > 0; l--){
				maxv = max(maxv, a[l]);
				sumv += a[l];
				
				if(j != 0) dp[i][j] = min(dp[i][j], dp[l - 1][j - 1] + maxv * (i - l + 1) - sumv);
			}
			
			maxv = max(maxv, a[0]);
			sumv += a[0];
			dp[i][j] = min(dp[i][j], maxv * (i + 1) - sumv);
		}
	}
	
	cout << dp[n - 1][k] << endl;

	return 0;
}