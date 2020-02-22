#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 15;
int n, m;
int a[maxn], ans[maxn];
int s[1 << maxn];
int dp[maxn][1 << maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 0; i < (1 << n); i++)
	for(int j = 0; j < n; j++){
		s[i] += ((i >> j) & 1) * a[j];
	} 
	
	for(int i = 0, c = 0; i < m; i++){
		int x;
		cin >> x;
		c += x;
		
		for(int j = 1; j < (1 << n); j++){
			dp[i][j] = ((!i || dp[i - 1][j]) && s[j] == c) * j;
		}
		
		for(int j = 0; j < n; j++)
		for(int k = 1; k < (1 << n); k++){
			if(!dp[i][k]) dp[i][k] = ((k >> j) & 1) * dp[i][k ^ (1 << j)];
		}
	}
	
	if(!dp[m - 1][(1 << n) - 1]){
		cout << -1 << endl;
		return 0;
	}
	
	for(int i = m - 1, j = dp[m - 1][(1 << n) - 1]; i >= 0; i--, j = dp[i][j]){
		ans[i] = j ^ (i ? dp[i - 1][j] : 0);
	}
	
	for(int i = 0; i < m; i++){
		cout << __builtin_popcount(ans[i]);
		for(int j = 0; j < n; j++) if(ans[i] & (1 << j)) cout << " " << j + 1;
		cout << endl;
	}

	return 0;
}