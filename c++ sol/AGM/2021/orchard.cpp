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

const int mxn = 1000, mxk = 1000, w = 101;
int n, m, k;
int par[mxk], rnk[mxk];
int f[mxk][w], dp[mxk][w];
int a[mxn][mxn];

int fnd(int x){ return x == par[x] ? x : par[x] = fnd(par[x]);}

void unf(int x, int y){
	x = fnd(x), y = fnd(y);
	if(x == y) return;
	if(rnk[x] < rnk[y]) swap(x, y);
	rnk[x] += rnk[x] == rnk[y];
	par[y] = x;
	for(int i = 0; i < w; i++) f[x][i] += f[y][i];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	memset(a, -1, sizeof(a));
	for(int i = 0; i < k; i++){
		int x, y, X, Y;
		cin >> x >> y >> X >> Y;
		x--, y--;
		par[i] = i, par[k + i] = k + i;
		for(int j = x; j < X; j++)
		for(int l = y; l < Y; l++){
			a[j][l] = i; 
		}
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		int z;
		cin >> z;
		if(~a[i][j]){ 
			f[fnd(a[i][j])][z]++;
			for(int l = 0; l < 4; l++){
				int x = i - min(1, l), y = j + max(-1, l - 2);
				if(~x && ~y && y < m && ~a[x][y] && a[x][y] != a[i][j]){
					unf(a[i][j], k + a[x][y]);
					unf(k + a[i][j], a[x][y]);
					if(fnd(a[i][j]) == fnd(k + a[i][j])){
						cout << -1 << endl;
						return 0;
					}
				}
			}
		}
	}
	
	for(int i = 0; i < 2 * k; i++) if(fnd(i) == i){
		for(int j = 0; j < w; j++)
		for(int l = 0; l < w; l++){
			dp[i][j] += abs(j - l) * f[i][l];
		}
	}
	
	
	int ret = 0x3f3f3f3f;
	for(int i = 0; i < w; i++)
	for(int j = 0; j < w; j++) if(i != j){
		int z = 0;
		for(int l = 0; l < 2 * k; l++){ 
			int x = fnd(l), y = fnd((k + l) % (2 * k));
			if(l == min(x, y)) z += min(dp[x][i] + dp[y][j], dp[x][j] + dp[y][i]);
		}
		ret = min(ret, z);
	}
	
	cout << ret << endl;
	
	return 0;
}