#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
const long long inf = 2e18 + 7;
const int l = 100;
int n, m, k;
 
long long f[l][l];
long long g[l][l];

void fill(long long a[l][l]){
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) a[i][j] = inf;
}

void print(long long a[l][l]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) cout << a[i][j] << " ";
		cout << endl;
	} 
	cout << endl;
}
 
void mult(long long a[l][l], long long b[l][l]){
	long long ret[l][l];
	fill(ret);
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k < n; k++){
		ret[i][j] = min(ret[i][j], a[i][k] + b[k][j]);
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		a[i][j] = ret[i][j];
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	fill(f);
	fill(g);
	
	for(int i = 0; i < n; i++) f[i][i] = 0;
	
	for(int i = 0; i < m; i++){
		long long a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		g[b][a] = min(g[b][a], c);
	}
	
	for(; k > 0; k >>= 1){
		if(k & 1) mult(f, g);
		mult(g, g);
	}
	
	cout << (f[n - 1][0] == inf ? -1 : f[n - 1][0]) << endl;
 
	return 0;
}