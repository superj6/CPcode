#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <math.h>
#include <complex>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int m = 1 << 13;
typedef double ld;
typedef complex<ld> cd;
const ld PI = acos(-1);

void fft(cd v[m], int f){
	for(int i = 1, j = 0, l; i < m; i++){
		for(l = m >> 1; j & l; l >>= 1) j ^= l;
		if(i < (j ^= l)) swap(v[i], v[j]);
	}
	
	for(int l = 1; l < m; l <<= 1){
		ld ang = PI / l * (1 - 2 * f);
		cd wl(cos(ang), sin(ang));
		for(int i = 0; i < m; i += l << 1){
			cd w(1);
			for(int j = 0; j < l; j++){
				cd x = v[i + j], y = w * v[i + j + l];
				v[i + j] = x + y, v[i + j + l] = x - y;
				w *= wl;
			}
		}
	}
	
	if(f) for(int i = 0; i < m; i++) v[i] /= m;
}

const int mod = 31333;
const int mxn = 3500;
int n, k;
int a[mxn], b[mxn];
cd vx[m], vy[m];
int dp[mxn][mxn];
vector<int> g[mxn];

int dfs(int c, int p){
	dp[c][a[c]] = b[c] = 1;
	for(int i : g[c]){
		if(i == p) continue;
		(b[c] *= 2 * dfs(i, c)) %= mod;
		
		for(int j = 0; j < m; j++) vx[j] = vy[j] = cd(0);
		for(int j = 0; j <= k; j++){
			vx[j] = dp[c][j], vy[j] = dp[i][j];
		}
		vy[0] += b[i];
		
		fft(vx, 0), fft(vy, 0);
		for(int j = 0; j < m; j++) vx[j] *= vy[j];
		fft(vx, 1);
		
		for(int j = 0; j <= k; j++) dp[c][j] = (ll)roundl(vx[j].real()) % mod;
	}
	return b[c];
}

int main(){
	freopen("radare.in", "r", stdin);
	freopen("radare.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 0; i < n; i++) cin >> a[i];
	
	dfs(0, -1);
	
	cout << dp[0][k] << endl;

	return 0;
}