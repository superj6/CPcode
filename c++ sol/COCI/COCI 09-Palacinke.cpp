/*
	Realize we can use matrix exponentiation to find number of paths between two points after t steps, and we can
hold two copies of each node to represent the number of paths in t steps and number of paths in t - 1 steps so we
can transition forward by two when we use the shop on an edge. Also I hold a sink node that can only be stepped into
by the first node to count all paths less than or equal to t. Now to find paths that visit stores with all 4 items,
realize you can do inclusion exclusion to subtract out paths that only use subsets of the full amount of stores. This
results in a time complexity of O(n^3 * lgt * 2^k), where k is number of store items.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <bitset>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 5557;
const int mxn = 25, mxm = 500, k = 4;
const char c[k] = {'B', 'J', 'M', 'P'};
int n, m, t;
int u[mxm], v[mxm], w[mxm];

struct M{
	int v[2 * mxn + 1][2 * mxn + 1];
	
	M(){ memset(v, 0, sizeof(v));}
	
	friend M operator*(M &x, M &y){
		M ret;
		for(int i = 0; i <= 2 * n; i++)
		for(int j = 0; j <= 2 * n; j++)
		for(int l = 0; l <= 2 * n; l++){
			(ret.v[i][j] += x.v[i][l] * y.v[l][j]) %= mod;
		}
		return ret;
	}
} a, b;

int f(int x, int y){
	return x + y * n;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		string s;
		cin >> u[i] >> v[i] >> s;
		u[i]--, v[i]--;
		for(char j : s) w[i] |= (1 << (find(c, c + k, j) - c));
	}
	
	cin >> t;
	t++;
	
	ll ret = 0;
	for(int p = 0; p < (1 << k); p++){
		a = M(), b = M();
		a.v[0][2 * n] = 1;
		a.v[2 * n][2 * n] = 1;
		for(int i = 0; i < n; i++){
			a.v[f(i, 0)][f(i, 1)] = 1;
			for(int l = 0; l < 2; l++) b.v[f(i, l)][f(i, l)] = 1;
		}
		
		for(int i = 0; i < m; i++){
			a.v[f(u[i], 0)][f(v[i], 0)] = 1;
			if((w[i] & p) == w[i]) a.v[f(u[i], 1)][f(v[i], 0)] = 1;
		}
		
		cin >> t;
		
		for(int i = t; i; i >>= 1){
			if(i & 1) b = b * a;
			a = a * a;
		}
		
		(ret += mod + (1 - 2 * (__builtin_popcount(p) & 1)) * b.v[0][2 * n]) %= mod;
	}
	
	cout << ret << endl; 

	return 0;
}