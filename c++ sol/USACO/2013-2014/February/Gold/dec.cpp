#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

int main(){
	freopen("dec.in", "r", stdin);
	freopen("dec.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, b;
	cin >> n >> b;
	
	vector<pair<int, int>> bonus[n];
	
	for(int i = 0; i < b; i++){
		int k, p, a;
		cin >> k >> p >> a;
		k--;
		
		bonus[k].push_back(make_pair(p, a));
	}
	
	for(int i = 0; i < n; i++){
		sort(bonus[i].begin(), bonus[i].end());
	}
	
	int cows[n][n];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> cows[i][j];
		}
	}
	
	int dp[1 << n];
	dp[0] = 0;
	
	for(int i = 1; i < (1 << n); i++){
		dp[i] = 0;
		int b = __builtin_popcount(i) - 1;
		
		for(int j = 0; j < n; j++){
			if(i & (1 << j)){
				dp[i] = max(dp[i], dp[i ^ (1 << j)] + cows[j][b]);
			}
		}
		
		for(int j = 0; j < bonus[b].size(); j++){
			if(bonus[b][j].first > dp[i]) break;
			dp[i] += bonus[b][j].second;
		}
	}
	
	cout << dp[(1 << n) - 1] << endl;

	return 0;
}