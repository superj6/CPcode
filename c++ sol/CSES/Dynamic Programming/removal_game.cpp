#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 5000;
int n;
long a[maxn];
long dp[maxn][maxn];

long recur(int l, int r){
	if(dp[l][r] != -1) return dp[l][r];
	
	if(l == r){
		dp[l][r] = n % 2 ? a[l] : 0;
	}else if(n % 2 == (r - l + 1) % 2){
		dp[l][r] = max(recur(l + 1, r) + a[l], recur(l, r - 1) + a[r]);
	}else{
		dp[l][r] = min(recur(l + 1, r), recur(l, r - 1));
	}
	
	return dp[l][r];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	memset(dp, -1, sizeof(dp));
	
	cout << recur(0, n - 1) << endl;

	return 0;
}