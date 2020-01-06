#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000;
int n;
int a[maxn];
long long dp[maxn][maxn][2];

long long solve(int l, int r, int x){
	if(dp[l][r][x]) return dp[l][r][x];
	if(l == r) return dp[l][r][x] = n * abs(a[l]);
	
	dp[l][r][x] = 100000000000000007;
	if(x){
		if(a[r - 1] > 0) dp[l][r][x] = min(dp[l][r][x], 
		(n + l - r) * (a[r] - a[r - 1]) + solve(l, r - 1, 1));
		if(a[l] < 0) dp[l][r][x] = min(dp[l][r][x], 
		(n + l - r) * (a[r] - a[l]) + solve(l, r - 1, 0));
	}else{
		if(a[r] > 0) dp[l][r][x] = min(dp[l][r][x], 
		(n + l - r) * (a[r] - a[l]) + solve(l + 1, r, 1));
		if(a[l + 1] < 0) dp[l][r][x] = min(dp[l][r][x],
		(n + l - r) * (a[l + 1] - a[l]) + solve(l + 1, r, 0));
	}
	
	return dp[l][r][x];
}

int main(){
	freopen("cowrun.in", "r", stdin);
	freopen("cowrun.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	sort(a, a + n);
	
	cout << min(solve(0, n - 1, 0), solve(0, n - 1, 1)) << endl;

	return 0;
}