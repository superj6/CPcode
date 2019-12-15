/*
	This problem is just pretty simple dp. Hold the states as dp[i][j] being the minimum wasted space using the first i snakes
and j changes in size. To calculate this state from the previous, you just need to for every l less than i find the sum from l to
i and the maximum value from l to i, as all snakes need to be able to fit with that size, then set dp[i][j] as dp[l - 1][j - 1] +
maxv * (i - l + 1) - sumv as that is setting the net to maxv for all sizes and and subtracting the actual amount used to find the
wasted space and adding it to the best solution using 1 less transition before l. As long as you iterate l backwards from i and
hold the max and sum as you go, the time complexity will be O(n^3).
*/

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
