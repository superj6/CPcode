#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	int a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	pi dp[1 << n];
	dp[0] = {0, 0};
	for(int i = 1; i < (1 << n); i++){
		dp[i] = {n + 1, m};
		for(int j = 0; j < n; j++){
			if(i & (1 << j)){
				if(a[j] <= -dp[i ^ (1 << j)].second){
					dp[i] = min(dp[i], {dp[i ^ (1 << j)].first, dp[i ^ (1 << j)].second + a[j]});
				}else{
					dp[i] = min(dp[i], {dp[i ^ (1 << j)].first + 1, -m + a[j]});
				}
			}
		}
	}
	
	cout << dp[(1 << n) - 1].first << endl;

	return 0;
}