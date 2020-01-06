#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int sz = 70;

int main(){
	freopen("262144.in", "r", stdin);
	freopen("262144.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int maxv = 0;
	int a[n];
	int dp[n][sz + 1];
	for(int i = 0; i < n; i++){
		cin >> a[i];
		dp[i][0] = -1;
	} 
	
	
	
	for(int j = 1; j <= sz; j++){
		for(int i = 0; i < n; i++){
			if(a[i] == j) dp[i][j] = i + 1;
			else if(dp[i][j - 1] != n && dp[i][j - 1] != -1 && dp[dp[i][j - 1]][j - 1] != -1) dp[i][j] = dp[dp[i][j - 1]][j - 1];
			else(dp[i][j]) = -1;
			
			if(dp[i][j] != -1) maxv = max(maxv, j);
		}
	}
	
	cout << maxv << endl;

	return 0;
}