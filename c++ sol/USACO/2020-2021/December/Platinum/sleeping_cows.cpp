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
const int mxn = 3001;
int n;
pi a[mxn << 1];
ll dp[mxn][2], dp2[mxn][2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= 2 * n; i++) cin >> a[i].f, a[i].s = 2 * (i > n) - 1;
	
	sort(a + 1, a + 2 * n + 1);
	
	dp[0][0] = 1;
	for(int i = 1, k = 0; i <= 2 * n; i++){
		k -= a[i].s;
		swap(dp, dp2);
		memset(dp, 0, sizeof(dp));
 		for(int j = max(k, 0); j <= n; j++){
	 		for(int l = 0; l < 2; l++){
	 			if(a[i].s == 1 - 2 * l) dp[j][l] = dp2[j][l];
	 			if(j + a[i].s >= 0){
	 				if(!~a[i].s) (dp[j][l] += dp2[j - 1][l]) %= mod; 
	 				else (dp[j][l] += (j + 1) * dp2[j + 1][l]) %= mod;
	 			}
			}
			if(!~a[i].s) (dp[j][1] += dp2[j][0]) %= mod;
 		}
	}
	
	ll ret = (dp[0][0] + dp[0][1]) % mod;
	
	cout << ret << endl;

	return 0;
}