#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007, i2 = (mod + 1) / 2;
const int maxn = 50001, maxk = 20;
int n, k, q;
int a[maxn];
long long m[maxk][maxk], im[maxk][maxk];
long long dp[maxn][maxk], idp[maxn][maxk];

int main(){
	freopen("nondec.in", "r", stdin);
	freopen("nondec.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	idp[0][0] = 1;
	for(int i = 0; i < k; i++) m[i][i] = im[i][i] = dp[0][i] = 1;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i]--;
		
		for(int j = 0; j <= a[i]; j++){
			for(int l = a[i]; l >= j; l--){
				m[j][a[i]] += m[j][l];
				m[j][a[i]] %= mod;
			}
			for(int l = a[i]; l < k; l++){
				im[j][l] += mod - i2 * im[a[i]][l] % mod;
				im[j][l] %= mod;
			}
		}
		
		for(int j = 0; j < k; j++){
			for(int l = 0; l < k; l++){
				dp[i][j] += m[j][l];
				dp[i][j] %= mod;
			}
			idp[i][j] = im[0][j];
		}
	}
	
	cin >> q;
	
	for(int i = 0; i < q; i++){
		int l, r;
		cin >> l >> r;
		int ret = 0;
		for(int j = 0; j < k; j++){
			ret += idp[l - 1][j] * dp[r][j] % mod;
			ret %= mod;
		}
		cout << ret << endl;
	}

	return 0;
}