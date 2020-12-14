#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 6000000, mxm = 30;
int n, m;
int a[mxn];
int f[mxm][2], g[mxm][2], vis[mxm][2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> m >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		for(int j = 0; j < 3; j++) a[i + j * n] = a[i];
		for(int j = 0, x = a[i]; j < m; j++, x >>= 1) vis[j][x & 1] = 1;
	}
	
	ll ret = 0;
	for(int i = 0; i < 2 * n; i++){
		int x = i, y = i;
		for(int j = 0; j < m; j++)
		for(int l = 0; l < 2; l++){
			if(vis[j][l]){
				if(i == g[j][l]){
					f[j][l] = i;
					for(g[j][l]++; ((a[g[j][l]] >> j) & 1) != l; g[j][l]++);
				}
				x = min(x, f[j][l]);
				y = max(y, g[j][l]);
			}
		}
		if(i >= n) ret += max(0, n - (y - x));
	}
	ret /= 2;
	
	cout << ret << endl;

	return 0;
}