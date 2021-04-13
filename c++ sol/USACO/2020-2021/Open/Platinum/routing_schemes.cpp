#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 101;
int n, m, k;
ll a[mxn], f[mxn], vv[mxn];
int g[mxn][mxn], ve[mxn][mxn];

//goes along each path and at each endpoint tries next vertex
int sol(int x, int y){
	if(x == n) return !m;
	if(~a[x]) return sol(x + 1, x + 1);
	int ret = 0;
	if(!vv[y]) vv[y] = 1, ret += sol(x + 1, x + 1), vv[y] = 0;
	for(int i = 0; i < n; i++){
		if(g[y][i] && !ve[y][i]){
			m--, ve[y][i] = 1;
			ret += sol(x, i);
			m++, ve[y][i] = 0;
		}
	}
	return ret;
}

void answer(){
	cin >> n >> k;
	m = 0;
	
	for(int i = 0; i < n; i++){
		char c;
		cin >> c;
		a[i] = c == 'S' ? -1 : c == 'R';
		vv[i] = ~-a[i];
	}

	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		g[i][j] = c & 1;
		m += g[i][j];
	}
	
	if(k){
		//brute force paths
		cout << sol(0, 0) << endl;
	}else{
		//just multiply partitions to next for each vertex due to guaranteed sol
		ll ret = 1;
		for(int i = 0; i < n; i++){
			(ret *= f[count(g[i], g[i] + n, 1) + !~-a[i]]) %= mod;
		}
		cout << ret << endl;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	f[0] = 1;
	for(int i = 1; i < mxn; i++) (f[i] = i * f[i - 1]) %= mod;
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}