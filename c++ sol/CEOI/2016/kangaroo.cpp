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

const int mod = 1000000007;
const int mxn = 2001;
int n, x, y;
int dp[2][mxn];
int r;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> x >> y;
	
	dp[r++][0] = 1;
	for(int i = 1, l = 0; i <= n; i++, r ^= 1){
		int t = i == x || i == y;
		dp[r][0] = 0;
		for(int j = 1; j <= n; j++){
			if(t){
				dp[r][j] = (dp[!r][j] + dp[!r][j - 1]) % mod;
			}else{
				dp[r][j] = ((ll)max(0, j - l) * dp[!r][j - 1] + (ll)j * dp[!r][j + 1]) % mod;
			}
		}
		l += t;
	}
	r ^= 1;
	
	cout << dp[r][1] << endl;

	return 0;
}