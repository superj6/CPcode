/*

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 998244353;
const int mxn = 45, mxk = 10, mxm = 2 * mxn * 4 * mxk;
int n, m, k, w, l;
int g[mxn][mxn];
ll a[mxm], b[mxm], s[mxm], t[mxm], z[mxm];
int dp[2][mxm];
vector<int> v, v1, v2;
vector<int> gr[mxm];

int f(int x, int y, int z){
	return x + n * y + n * 4 * z;
}

int ipow(ll b, int e){
	int ret = 1;
	for(; e; e >>= 1){
		if(e & 1) ret = ret * b % mod;
		b = b * b % mod;
	}
	return ret;
}

void mul(ll *x, ll *y){
	memset(z, 0, 2 * l * sizeof(ll));
	for(int i = 0; i < l; i++) if(x[i])
	for(int j = 0; j < l; j++){
		(z[i + j] += x[i] * y[j]) %= mod;
	}
	for(int i = 2 * l - 1; i >= l; i--) if(z[i])
	for(int j = 0; j < l; j++){
		(z[i - j - 1] += z[i] * v[j]) %= mod;
	}
	memcpy(x, z, l * sizeof(ll));
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> w >> k;
	k += 2, m = n * 4 * k, w--;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		g[i][j] = c & 1;
	}
	
	//create graph
	for(int j = 0; j < 4; j++)
	for(int l = 0; l < k; l++)
	for(int i = j || l; i < n; i++){
		int x = f(i, j, l);
		for(int p = 1; p < 3; p++){
			if(g[i][p]) gr[x].push_back(f(p, j | (1 << (p - 1)), l));
		}
		if(g[i][3]) gr[x].push_back(f(3, j, min(k - 1, l + 1)));
		for(int p = 4; p < n; p++){
			if(g[i][p]) gr[x].push_back(f(p, j, l));
		}
	}
	
	
	dp[0][0] = 1;
	for(int i = 1, r = 1, p = 0; i < 2 * m; i++, r ^= 1){
		//dumb dp
		memset(dp[r], 0, sizeof(dp[r]));
		for(int j = 0; j < m; j++)
		for(int l : gr[j]){
			(dp[r][l] += dp[r ^ 1][j]) %= mod;
		}
		a[i] = dp[r][f(n - 1, 3, k - 2)];
		
		//berk-mass
		b[i] = (mod - a[i]) % mod;
		for(int j = 0; j < v.size(); j++) (b[i] += a[i - j - 1] * v[j]) %= mod;
		if(!b[i]) continue;
		if(v.empty()){
			p = i;
			v.resize(i + 1);
			continue;
		}
		swap(v, v1);
		v.assign(i - p - 1, 0);
		ll x = (mod - b[i] * ipow(b[p], mod - 2) % mod) % mod;
		v.push_back((mod - x) % mod);
		for(int j = 0; j < v2.size(); j++) v.push_back(x * v2[j] % mod);
		if(v.size() < v1.size()) v.resize(v1.size());
		for(int j = 0; j < v1.size(); j++) (v[j] += v1[j]) %= mod;
		if(i - p + v2.size() >= v1.size()) p = i, swap(v1, v2);
	}
	
	//poly find wth term
	l = v.size();
	s[0] = t[1] = 1;
	for(; w; w >>= 1){
		if(w & 1) mul(s, t);
		mul(t, t);
	}
	
	ll ret = 0;
	for(int i = 0; i < l; i++) (ret += s[i] * a[i]) %= mod;
	
	cout << ret << endl;

	return 0;
}
