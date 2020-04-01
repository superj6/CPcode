#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000, k = 17;
int n, m, q;
int a[maxn], b[maxn], d[maxn];
int p[k][maxn];
bool used[maxn], h[maxn];
vector<int> graph[maxn];
int t;

void dfs(int c){
	used[c] = 1;
	a[c] = b[c] = t++;
	int amt = 0;
	for(int i : graph[c]){
		if(i == p[0][c]) continue;
		if(used[i]) b[c] = min(b[c], a[i]);
		else{
			amt++;
			p[0][i] = c;
			d[i] = d[c] + 1;
			dfs(i);
			b[c] = min(b[c], b[i]);
			if(b[i] >= a[c] && p[0][c] != -1) h[c] = 1;
		}
	}
	if(p[0][c] == -1 && amt > 1) h[c] = 1;
}

int lca(int x, int y){
	if(d[x] < d[y]) swap(x, y);
	for(int i = k - 1; i >= 0; i--) if(p[i][x] != -1 && d[p[i][x]] >= d[y]) x = p[i][x];
	for(int i = k - 1; i >= 0; i--) if(p[i][x] != p[i][y]) x = p[i][x], y = p[i][y];
	return x == y ? x : p[0][x];
}

int dist(int x, int y){
	return d[x] + d[y] - 2 * d[lca(x, y)];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> q;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	p[0][0] = -1;
	dfs(0);
	
	for(int i = 1; i < k; i++)
	for(int j = 0; j < n; j++){
		p[i][j] = p[i - 1][j] == -1 ? -1 : p[i - 1][p[i - 1][j]];
	}
	
	for(int i = 0; i < q; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--, c--;
		cout << (h[c] && dist(a, b) == dist(a, c) + dist(c, b) ? "NO" : "YES") << endl;
	}

	return 0;
}