#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 500000, mxm = 19, mxk = 10;
int n, m, k, w;
int a[mxn];
int dp[2][1 << mxm][mxk];
vector<int> v;
int r;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	sort(a, a + n);
	
	dp[0][0][0] = 1;
	for(int i = 0; i < n; i++){
		if(a[i]) m = max(m, __lg(a[i]) + 1);
		
		if(m <= mxm){
			for(int j = 0; j < (1 << m); j++)
			for(int l = 1; l <= k; l++){
				dp[r ^ 1][j][l % k] = (dp[r][j][l % k] + dp[r][j ^ a[i]][l - 1]) % mod;
			}
			r ^= 1;
		}else{
			v.push_back(a[i]);
		}
	}
	
	w = v.size();
	int ret = !(n % k) * (mod - 1);
	for(int i = 0; i < (1 << w); i++){
		int c = 0, p = __builtin_popcount(i);
		if(p & 1) continue;
		for(int j = 0; j < w; j++) if((i >> j) & 1) c ^= v[j];
		(ret += dp[r][c][(n - p) % k]) %= mod;
	}
	
	cout << ret << endl;

	return 0;
}