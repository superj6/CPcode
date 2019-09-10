#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
const int mod = 1e9 + 7;
const int l = 100;
 
long long f[l][l];
long long g[l][l];
 
void mult(long long a[l][l], long long b[l][l]){
	long long ret[l][l];
	memset(ret, 0, sizeof(ret));
	for(int i = 0; i < l; i++)
	for(int j = 0; j < l; j++)
	for(int k = 0; k < l; k++){
		ret[i][j] += (a[i][k] * b[k][j]) % mod;
		ret[i][j] %= mod;
	}
	
	for(int i = 0; i < l; i++)
	for(int j = 0; j < l; j++){
		a[i][j] = ret[i][j];
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) f[i][i] = 1;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[b][a]++;
	}
	
	for(; k > 0; k >>= 1){
		if(k & 1) mult(f, g);
		mult(g, g);
	}
	
	cout << f[n - 1][0] << endl;
 
	return 0;
}