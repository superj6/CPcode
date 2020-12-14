#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int n = 20, k = 10;
ll l, r;
int a[n];
ll dp[n][k][k][3][2];

ll sol(ll x){
	if(x < 0) return 0;
	memset(dp, 0, sizeof(dp));
	for(int i = n - 1; ~i; i--, x /= 10) a[i] = x % 10;
	
	dp[0][0][0][0][0] = 1;
	for(int i = 1; i < n; i++)
	for(int j1 = 0; j1 < k; j1++)
	for(int j2 = 0; j2 < k; j2++)
	for(int j3 = 0; j3 < k; j3++)
	for(int l1 = 0; l1 < 3; l1++)
	for(int l2 = 0; l2 < 2; l2++){
		if((l1 && j2 == j3) || (l1 > 1 && j1 == j3) || (!l2 && j3 > a[i])) continue;
		dp[i][j2][j3][min(2, l1 + (l1 || j3))][l2 || j3 < a[i]] += dp[i - 1][j1][j2][l1][l2];
	}
	
	ll ret = 0;
	for(int j1 = 0; j1 < k; j1++)
	for(int j2 = 0; j2 < k; j2++)
	for(int l1 = 0; l1 < 3; l1++)
	for(int l2 = 0; l2 < 2; l2++){
		ret += dp[n - 1][j1][j2][l1][l2];
	}
	
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> l >> r;
	
	cout << sol(r) - sol(l - 1) << endl;

	return 0;
}