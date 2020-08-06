/*
  Simulate finding outer walls, destroying them, then finding inner walls. To do always start from farthest left point with untouched
wall and dfs while always choosing to travel along the rightmost edge as possible to make sure you get the outermost loop. When you find
a loop, mark all the edges as touched, and at the end print all edges that were never touched.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int mxn = 200000, k = 4;
int n, m;
int a[mxn][2];
int u[mxn], v[mxn], it[mxn], vis[mxn], vis2[mxn], f[mxn];
int g[mxn][k];
 
bool dfs(int c, int p){
	vis[c] = 1;
	for(int i = (p + 1) % k; i != p; i = (i + 1) % k){
		int x = g[c][i];
		if(!~x || vis2[x]) continue;
		vis2[x] = 1;
		int y = c ^ u[x] ^ v[x];
		if(!vis[y]){
			if(dfs(y, (i + 2) % k)){
				f[x] = 1;
				if(~vis[c]){
					vis[c] = 0;
					return 1;
				}
				vis[c] = 1;
			}
		}else if(!~-vis[y]){
			f[x] = 1;
			vis[c] = 0, vis[y] = -1;
			return 1;
		}
	}
	vis[c] = 0;
	return 0;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 2; j++) cin >> a[i][j];
		it[i] = i;
	} 
	
	cin >> m;
	
	memset(g, -1, sizeof(g));
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i];
		u[i]--, v[i]--;
		for(int j = 0; j < 2; j++){
			if(a[u[i]][!j] == a[v[i]][!j]){
				int x = (a[u[i]][j] < a[v[i]][j]) << 1 | j;
				g[u[i]][x] = i, g[v[i]][(x + 2) % k] = i;
			}
		}
	}
	
	sort(it, it + n, [&](int x, int y){
		return a[x][0] < a[y][0];
	});
	
	for(int i = 0; i < n; i++)
	for(int j = 1; j < k; j++){
		int x = g[it[i]][j];
		if(~x && !vis2[x]) dfs(it[i], 0);
	}
	
	int ret = 0;
	for(int i = 0; i < m; i++) ret += !f[i];
	
	cout << ret << endl;
	for(int i = 0; i < m; i++) if(!f[i]) cout << i + 1 << endl;
 
	return 0;
}
