#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 20;
int n;
int a[1 << maxn], dp[1 << maxn], dp2[1 << maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		dp[a[i]]++;
		dp2[a[i]]++;
	}
	
	for(int j = 0; j < maxn; j++)
	for(int i = 0; i < (1 << maxn); i++){
		if(i & (1 << j)) dp[i] += dp[i ^ (1 << j)];
		else dp2[i] += dp2[i ^ (1 << j)];
	}
	
	for(int i = 0; i < n; i++){
		cout << dp[a[i]] << " " << dp2[a[i]] << " " << n - dp[a[i] ^ ((1 << maxn) - 1)] << endl;
	}

	return 0;
}