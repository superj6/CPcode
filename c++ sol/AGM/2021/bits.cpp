#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000, w = 21, mxk = 30 * mxn;
int n, m, k;
int a[mxn], b[mxn], c[mxk], d[mxk], s[1 << w];
unordered_map<int, int> f[w][w], ff[w][w];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 0; i < m; i++){
		cin >> b[i];
		for(int j = __lg(b[i]); ~j; j--){
			c[k] = j, d[k++] = (b[i] >> j) & 1;
			for(int l = 0, x = 0; l < min(w, k); l++){
				s[x |= (d[k - l - 1] << l)] = 1;
				for(int p = 0; p <= l; p++){
					int y = c[k - p - 1];
					if(!f[l][p].count(x)){
						f[l][p][x] = ff[l][p][x] = y;
					}else{
						f[l][p][x] = min(f[l][p][x], y);
						ff[l][p][x] = max(ff[l][p][x], y);
					}
				}
			}
		} 
	}
	
	for(int i = 0; i < n; i++){
		int x = 1 << w, y = -1, z = __lg(a[i]);
		if(s[a[i]]) x = 0, y = 0;
		for(int j = 0; j <= z; j++){
			int v = a[i] ^ (1 << j);
			if(f[z][j].count(v)){
				x = min(x, 1 << f[z][j][v]);
				y = max(y, 1 << ff[z][j][v]);
			} 
		}
		cout << (~y ? x : y) << " " << y << endl;
	}
	
	return 0;
}