#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 10000000;
int n;
int dp[maxn], f[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	dp[0] = 1;
	f[0] = f[1] = 1;
	for(int i = 1; f[i] < maxn; i++){
		f[i + 1] = f[i] + f[i - 1];
		for(int j = maxn - f[i] - 1; j >= 0; j--){
			dp[j + f[i]] += dp[j];
		}
	}
	
	cin >> n;
	for(int i = 0, j = 0; i < n; i++){
		int x;
		cin >> x;
		j += f[x];
		cout << dp[j] << endl;
	}

	return 0;
}
