#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	freopen("talent.in", "r", stdin);
	freopen("talent.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, w;
	cin >> n >> w;
	
	pair<int, int> a[n];
	for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
	
	sort(a, a + n, [&](pair<int, int> f, pair<int, int> g){
		return 1.0 * f.first / f.second < 1.0 * g.first / g.second;
	});
	
	int dp[w];
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	
	int ans = 0;
	for(int i = 0; i < n; i++){
		int x = a[i].first, y = a[i].second;
		
		for(int j = w - 1; j >= 0; j--){
			if(dp[j] != -1){
				if(j + x < w) dp[j + x] = max(dp[j + x], dp[j] + y);
				else ans = max(ans, (int)(1000.0 * (dp[j] + y) / (j + x)));	
			}
		}
	}

	cout << ans << endl;

	return 0;
}