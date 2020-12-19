#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 200003;
const int mxn = 1000001;
int n;
ll f[mxn], iv[mxn], dp[mxn];

int main(){
	freopen("matcnt.in", "r", stdin);
	freopen("matcnt.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < 2; i++) f[i] = iv[i] = dp[i] = 1;
	for(int i = 2; i <= n; i++){
		f[i] = i * f[i - 1] % mod;
		iv[i] = mod - mod / i * iv[mod % i] % mod;
		dp[i] = (dp[i - 1] + (i >= 3 ? iv[i] * iv[2] % mod * dp[i - 3] : 0)) % mod;
	}
	
	ll ret = (mod + dp[n] - dp[n - 1]) * f[n] % mod * f[n] % mod;
	
	cout << ret << endl;

	return 0;
}