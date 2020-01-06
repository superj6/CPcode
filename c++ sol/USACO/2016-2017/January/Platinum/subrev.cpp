/*
	For this problem, the key thing to notice is that the each element of the array is
is less than 50, which is also the array size. This leads to the idea that you can hold a
dp state such that you keep the dp[i][j][k][m] is the maximum increasing subsequence within
the subarray from indices i to j, and the lowest value is greater than or equal to k and the
least value is less than or equal to m. Holding the minimum and maximum on both sides helps
because you can use the fact that can then see whether you can reverse indices i and j by
seeing if a[j] is greater than or equal to k and a[i] is greater than or equal to i, while
also trying transitions of using neither element or keeping them in order. The complexity
of this is O(n^4).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int a[50];
int dp[50][50][51][51];

int solve(int i, int j, int k, int m){
	if(dp[i][j][k][m] != -1) return dp[i][j][k][m];
	if(k > m) return -(1 << 20);
	if(i > j) return 0;
	if(i == j){
		if(a[i] >= k && a[j] <= m) return 1;
		else return 0;
	}
	
	int ret = 0;
	
	//////
		ret = max(ret, solve(i + 1, j - 1, k, m));
		if(a[j] >= k) ret = max(ret, solve(i + 1, j - 1, a[j], m) + 1);
		if(a[i] <= m) ret = max(ret, solve(i + 1, j - 1, k, a[i]) + 1);
		if(a[j] >= k && a[i] <= m && a[j] <= a[i]) ret = max(ret, solve(i + 1, j - 1, a[j], a[i]) + 2);
	//////
	
	//////
		ret = max(ret, solve(i + 1, j, k, m));
		if(a[i] >= k) ret = max(ret, solve(i + 1, j, a[i], m) + 1);
	//////
	
	//////
		ret = max(ret, solve(i, j - 1, k, m));
		if(a[j] <= m) ret = max(ret, solve(i, j - 1, k, a[j]) + 1);
	//////
	
	dp[i][j][k][m] = ret;
	return ret;
}

int main(){
	freopen("subrev.in", "r", stdin);
	freopen("subrev.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k <= 50; k++)
	for(int m = 0; m <= 50; m++){
		dp[i][j][k][m] = -1;
	}
	
	cout << solve(0, n - 1, 0, 50) << endl;;

	return 0;
}
