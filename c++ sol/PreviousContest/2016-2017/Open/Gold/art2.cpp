#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	freopen("art2.in", "r", stdin);
	freopen("art2.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	pair<int, int> col[n + 1];
	for(int i = 0; i <= n; i++) col[i] = {n, 0};
	
	for(int i = 0; i < n; i++){
		int c;
		cin >> c;
		col[c].first = min(col[c].first, i);
		col[c].second = max(col[c].second, i + 1);
	}
	
	int dp[n + 1];
	memset(dp, 0, sizeof(dp));
	for(int i = 1; i <= n; i++){
		if(col[i].first == n) continue;
		dp[col[i].first]++;
		dp[col[i].second]--;
	}
	
	sort(col, col + n + 1);
	
	for(int i = 0, r = -1; i <= n; i++){
		if(col[i].first < r && r < col[i].second){
			cout << -1 << endl;
			return 0;
		}
		r = col[i].second;
	}
	
	int maxv = 0;
	for(int i = 0, j = 0; i <= n; i++){
		j += dp[i];
		maxv = max(maxv, j);
	}
	
	cout << maxv << endl;

	return 0;
}