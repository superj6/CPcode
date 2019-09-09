#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int mod = 1000000007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	if(n * (n + 1) % 4 != 0){
		cout << 0 << endl;
		return 0;
	}
	
	int k = n * (n + 1) / 4;
	int dp[k + 1];
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	
	for(int i = 1; i <= n; i++){
		for(int j = k; j >= i; j--){
			dp[j] = (dp[j] + dp[j - i]) % mod;
		}
	}
	
	cout << (dp[k] + (dp[k] % 2 == 1 ? mod : 0)) / 2 << endl;

	return 0;
}