#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 501, m = 1000001;
int n, k;
int a[mxn], b[mxn][2], g[mxn][2];
ll f[m], rf[m], iv[m];
ll dp[mxn][mxn];
stack<int> stk;

ll C(int x, int y){
	return f[x] * rf[y] % mod * rf[x - y] % mod;
}

void dfs(int c, int p){
	dp[c][0] = 1;
	for(int i = 0, x; i < 2; i++) if(x = g[c][i]){
		dfs(x, c);
		b[c][i] = b[x][i];
		for(int j = k; j >= 0; j--)
		for(int l = 1; j + l <= k; l++){
			(dp[c][j + l] += dp[c][j] * dp[x][l]) %= mod;
		}
	} 
	int x = a[c] - a[p], y = b[c][1] - b[c][0] + 1;
	for(int i = k; i >= 0; i--)
	for(ll j = 1; j <= x && i + j <= y; j++){
		(dp[c][i + j] += f[j] * C(x, j) % mod * C(y - i, j) % mod * dp[c][i]) %= mod;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	stk.push(0);
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		b[i][0] = b[i][1] = i;
		while(a[i] < a[stk.top()]) g[i][0] = stk.top(), stk.pop();
		stk.push(g[stk.top()][1] = i);
	}
	
	f[0] = rf[0] = iv[0] = 1;
	for(int i = 1; i < m; i++){
		iv[i] = ~-i ? mod - mod / i * iv[mod % i] % mod : 1;
		f[i] = i * f[i - 1] % mod;
		rf[i] = iv[i] * rf[i - 1] % mod;
	}
	
	dfs(0, 0);
	
	cout << dp[0][k] << endl;

	return 0;
}