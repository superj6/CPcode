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

const int inf = 0x3f3f3f3f;
const int mxn = 300000;
int a[mxn][2];
int d[mxn], p[mxn], vis[mxn];
vector<int> g[mxn];
int ans[mxn];

void dfs(int c){
	vis[c] = 1;
	for(int i : g[c]){
		if(vis[i]) continue;
		d[i] = d[c] + 1;
		dfs(i);
	}
}

void answer(int x){
	cout << x << endl;
}

void count_routes(int n, int m, int k, int e[][2], int q, int qr[]){
	memset(a, inf, sizeof(a));
	memset(p, -1, sizeof(p));
	for(int i = 0; i < m; i++)
	for(int j = 0; j < 2; j++){
		int x = e[i][j];
		a[x][1] = min(a[x][1], i);
		sort(a[x], a[x] + 2);
	}
	
	for(int i = 0; i < n; i++){
		if(a[i][0] == inf){
			p[i] = i;
			g[i].push_back(i);
		}
	} 
	for(int i = 0; i < m; i++)
	for(int j = 0; j < 2; j++){
		int x = e[i][j], y = e[i][!j];
		for(int l = 0; l < 2; l++){
			if(a[x][l] == i){
				int u = (a[y][0] == i && a[y][1] != inf) * n + y, v = l * n + x;
				p[v] = u;
				g[u].push_back(v);
			} 
		}
	}
	
	for(int t = 0; t < 2; t++){
		memset(d, inf, sizeof(d));
		memset(vis, 0, sizeof(vis));
		
		int x = t * n + k, y, l;
		for(y = x; ~y && !vis[y]; y = p[y]) vis[y] = 1;
		for(int i = p[x]; i != y; i = p[i]) vis[i] = 0;
		
		d[x] = 0;
		dfs(x);
		if(x == y) l = d[p[x]] + 1;
		for(int i = 0; i < n; i++)
		for(int j = 0; j < q; j++){
			if(x != y) ans[j] += d[i] == qr[j];
			else ans[j] += d[i] <= qr[j] && (d[i] % l) == (qr[j] % l);
		}
	}
	
	for(int i = 0; i < q; i++) answer(ans[i]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m, k, q;
	int e[mxn][2], qr[mxn];
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < m; i++)
	for(int j = 0; j < 2; j++){
		cin >> e[i][j];
	}
	
	cin >> q;
	
	for(int i = 0; i < q; i++) cin >> qr[i];
	
	count_routes(n, m, k, e, q, qr);

	return 0;
}