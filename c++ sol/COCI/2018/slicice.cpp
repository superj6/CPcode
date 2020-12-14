#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 501;
int n, m, k;
ll a[mxn], b[mxn], dp[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i <= m; i++) cin >> b[i];
	
	ll ret = 0;
	for(int i = 0; i < n; i++){
		ret += b[a[i]];
		for(int j = k; ~j; j--)
		for(int l = a[i]; l <= m && j + l - a[i] <= k; l++){
			dp[j + l - a[i]] = max(dp[j + l - a[i]], dp[j] + b[l] - b[a[i]]);
		}
	}
	ret += dp[k];
	
	cout << ret << endl;

	return 0;
}