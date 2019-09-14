#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <iomanip>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int m = 8, n = m * m;
int k;
double f[n][n], g[n][n];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int p(int x, int y){
	if(x < 0 || x >= m || y < 0 || y >= m) return -1;
	return x * m + y;
}

void gen(){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < m; j++){
			f[p(i, j)][p(i, j)] = 1;
			int cnt = 0;
			for(int l = 0; l < 4; l++) if(p(i + dx[l], j + dy[l]) != -1) cnt++;
			for(int l = 0; l < 4; l++) if(p(i + dx[l], j + dy[l]) != -1) g[p(i + dx[l], j + dy[l])][p(i, j)] = 1.0 / cnt;
		}
	}
}

void mult(double a[n][n], double b[n][n]){
	double ret[n][n];
	memset(ret, 0.0, sizeof(ret));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			for(int l = 0; l < n; l++){
				ret[i][j] += a[i][l] * b[l][j];
			}
		}
	}
	
	memcpy(a, ret, sizeof(ret));
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout << setprecision(6) << fixed;
	
	gen();
	
	cin >> k;
	
	for(; k > 0; k >>= 1){
		if(k & 1) mult(f, g);
		mult(g, g);
	}
	
	double ret = 0;
	for(int i = 0; i < n; i++){
		double cur = 1;
		for(int j = 0; j < n; j++) cur *= (1 - f[i][j]);
		ret += cur;
	}
	
	cout << ret << endl;

	return 0;
}