#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100001;
int n, m;
int id[maxn], rid[maxn], p[maxn], sdom[maxn], dom[maxn];
int mn[maxn], par[maxn];
vector<int> g[maxn], rg[maxn], b[maxn];
int t;

int find(int x, int y = 0){
	if(x == par[x]) return y ? -1 : x;
	int v = find(par[x], 1);
	if(v < 0) return x;
	if(sdom[mn[par[x]]] < sdom[mn[x]]) mn[x] = mn[par[x]];
	par[x] = v;
	return y ? v : mn[x];
}

void unionf(int x, int y){
	par[y] = x;
}

void dfs(int c){
	rid[++t] = c;
	id[c] = mn[t] = sdom[t] = par[t] = t;
	for(int i : g[c]){
		if(!id[i]) dfs(i), p[id[i]] = id[c];
		rg[id[i]].push_back(id[c]);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
	}
	
	dfs(1);
	for(int c = n; c >= 1; c--){
		for(int i : rg[c]) sdom[c] = min(sdom[c], sdom[find(i)]);
		if(c > 1) b[sdom[c]].push_back(c);
		for(int i : b[c]){
			int v = find(i);
			if(sdom[i] == sdom[v]) dom[i] = sdom[i];
			else dom[i] = v;
		}
		if(c > 1) unionf(p[c], c);
	}
	for(int c = 2; c <= n; c++) if(dom[c] != sdom[c]) dom[c] = dom[dom[c]];
	
	vector<int> ans;
	for(int c = id[n]; c; c = dom[c]) ans.push_back(rid[c]);
	sort(ans.begin(), ans.end());
	
	cout << ans.size() << endl;
	cout << ans[0];
	for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}