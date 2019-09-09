#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int mw = 2001;
int n, w;
int dp[mw];

int main(){
	freopen("talent.in", "r", stdin);
	freopen("talent.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> w;
	
	int ans = 0;
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;

		if(x >= mw){
			ans = max(ans, (int)(1000.0 * y / x));
		}
		
		for(int j = mw - 1 - x; j >= 0; j--){
			if(dp[j] != -1){
				dp[j + x] = max(dp[j + x], dp[j] + y);
				if(w <= j + x) ans = max(ans, (int)(1000.0 * dp[j + x] / (j + x)));	
			}
		}
	}

	cout << ans << endl;

	return 0;
}