#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<int, pi>

const int maxn = 100002;
 
struct BIT{
	int bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
	
	void add(int a, int b, int v){
		add(a, v);
		add(b + 1, -v);
	}
 
	int qry(int x){
		int ret = 0;
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

const int k = 18;
int n, m;
BIT bit;
int l[maxn], r[maxn], dist[maxn];
int par[k][maxn];
vector<int> graph[maxn];
vector<int> p[maxn];
vector<pii> q[maxn];
bool ans[maxn];

int dfs(int c){
	r[c] = l[c];
	for(int i : graph[c]){
		if(i == par[0][c]) continue;
		l[i] = r[c] + 1;
		dist[i] = dist[c] + 1;
		par[0][i] = c;
		r[c] = dfs(i);
	}
	return r[c];
}

void precomp(){
	for(int i = 1; i < k; i++){
		for(int j = 0; j < n; j++){
			par[i][j] = (par[i - 1][j] == -1 ? -1 : par[i - 1][par[i - 1][j]]);
		}
	}
}

int lca(int x, int y){
	for(int i = k - 1; i >= 0; i--){
		if(par[i][x] != -1 && dist[y] <= dist[par[i][x]]) x = par[i][x];
		if(par[i][y] != -1 && dist[x] <= dist[par[i][y]]) y = par[i][y];	
	} 
	for(int i = k - 1; i >= 0; i--){
		if(par[i][x] != -1 && par[i][y] != -1 && par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	} 
	return x == y ? x : par[0][x];
}

int main(){
	freopen("milkvisits.in", "r", stdin);
	freopen("milkvisits.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		p[x].push_back(i);
	}
	
	for(int i = 0; i < n - 1; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	par[0][0] = -1;
	dfs(0);
	precomp();
	
	for(int i = 0; i < m; i++){
		int x, y, c;
		cin >> x >> y >> c;
		x--, y--, c--;
		q[c].push_back({i, {x, y}});
	}
	
	for(int i = 0; i < n; i++){
		for(int j : p[i]) bit.add(l[j], r[j], 1);
		
		for(pii j : q[i]){
			int x = j.second.first, y = j.second.second;
			int c = lca(x, y);
			int val = bit.qry(l[x]) + bit.qry(l[y]) - bit.qry(l[c]);
			if(par[0][c] != -1) val -= bit.qry(l[par[0][c]]);
			ans[j.first] = val > 0;
		}
		
		for(int j : p[i]) bit.add(l[j], r[j], -1);
	}
	
	for(int i = 0; i < m; i++) cout << ans[i];
	cout << endl;

	return 0;
}