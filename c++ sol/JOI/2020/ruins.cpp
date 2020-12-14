#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
#define ll long long

const int mod = 1000000007;
const int maxn = 603;
int n;
bool a[2 * maxn];
int p[maxn], dp[maxn], dp2[maxn];
int c[maxn][maxn], f[maxn][maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;

	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		a[x] = 1;
	}
	
	f[0][0] = 1;
	for(int i = 0; i < n; i++)
	for(int j = i; j <= 2 * i && j < n; j++){
		(f[i + 1][j + 2] += f[i][j]) %= mod;
		(f[i + 1][j + 1] += 2 * f[i][j] % mod) %= mod;
		(f[i + 1][j] += f[i][j]) %= mod;
	}

	c[0][0] = 1;
	for(int i = 0, j = 1; i < n; i++){
		p[i] = (ll)f[i][i] * j % mod * (i + 2) % mod;
		j = (ll)j * (i + 1) % mod;
		for(int k = 0; k <= i; k++){
			(c[i + 1][k] += c[i][k]) %= mod;
			(c[i + 1][k + 1] += c[i][k]) %= mod;
		}
	}

	dp[0] = 1;
	for(int i = 2 * n, x = 0, y = 0; i > 0 && y <= x; i--){
		if(a[i]){
			memcpy(dp2 + y, dp + y, (x - y + 1) * sizeof(int));
			for(int j = y; j <= x; j++)
			for(int k = j; k <= x; k++){
				(dp[k + 1] += (ll)dp2[j] * c[x - j][k - j] % mod * p[k - j] % mod) %= mod;
			}
			x++;
		}else{
			for(int j = y; j <= x; j++) dp[j] = (ll)dp[j] * (j - y) % mod;
			y++;
		}
	}

	int ret = dp[n];
	for(int i = n, j = (mod + 1) / 2; i; i >>= 1){
		if(i & 1) ret = (ll)ret * j % mod;
		j = (ll)j * j % mod;
	}

	cout << ret << endl;

	return 0;
}