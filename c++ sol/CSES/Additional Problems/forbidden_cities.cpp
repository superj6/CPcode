#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 100000, k = 17;
int n, m, q;
int a[maxn], b[maxn], d[maxn];
int p[k][maxn];
vector<int> graph[maxn];
vector<pi> g[maxn];
stack<pi> stk;
int s, t;

void setbicon(pi cp){
	for(pi p = {-2, -2}; !stk.empty() && p != cp; stk.pop()){
		p = stk.top();
		g[p.f].push_back({p.s, s});
		g[p.s].push_back({p.f, s});
	}
	s++;
}
 
void dfs(int c){
	a[c] = b[c] = ++t;
	int amt = 0;
	for(int i : graph[c]){
		if(p[0][c] == i) continue;
		if(!a[i]){
			amt++;
			p[0][i] = c;
			d[i] = d[c] + 1;
			stk.push({c, i});
			
			dfs(i);
			b[c] = min(b[c], b[i]);
			
			if(p[0][c] != -1 ? b[i] >= a[c] : amt > 1) setbicon({c, i});
		}else if(a[i] < b[c]){
			b[c] = a[i];
			stk.push({c, i});
		}
	}
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
	setbicon({-1, -1});
	
	for(int i = 0; i < n; i++) sort(g[i].begin(), g[i].end());
	
	for(int i = 1; i < k; i++)
	for(int j = 0; j < n; j++){
		p[i][j] = p[i - 1][j] == -1 ? -1 : p[i - 1][p[i - 1][j]];
	}
	
	for(int i = 0; i < q; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--, c--;
		bool t = (a != c && b != c);
		if(t && dist(a, b) == dist(a, c) + dist(b, c)){
			for(int j = k - 1; j >= 0; j--){
				if(p[j][a] != -1 && d[p[j][a]] > d[c]) a = p[j][a];
				if(p[j][b] != -1 && d[p[j][b]] > d[c]) b = p[j][b];
 			}
 			if(p[0][a] != c) a = p[0][c];
 			if(p[0][b] != c) b = p[0][c];
 			t &= (*lower_bound(g[c].begin(), g[c].end(), (pi){a, 0})).s == (*lower_bound(g[c].begin(), g[c].end(), (pi){b, 0})).s;
		}
		cout << (t ? "YES" : "NO") << endl;	}
 
	return 0;
}