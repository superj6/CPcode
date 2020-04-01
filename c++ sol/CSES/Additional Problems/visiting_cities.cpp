#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<long long, int>
#define f first
#define s second
 
const int maxn = 100001;
int n, m;
long long d[2][maxn];
int id[maxn], rid[maxn], p[maxn], sdom[maxn], dom[maxn];
int mn[maxn], par[maxn];
vector<int> g[maxn], rg[maxn], b[maxn];
vector<pi> graph[2][maxn];
set<pi> pq;
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
		int u, v, w;
		cin >> u >> v >> w;
		graph[0][u].push_back({v, w});
		graph[1][v].push_back({u, w});
	}
	
	for(int t = 0; t < 2; t++){
		int s = t * (n - 1) + 1;
		for(int i = 1; i <= n; i++) d[t][i] = 1000000000000007;
		d[t][s] = 0;
		pq.insert({0, s});
		while(!pq.empty()){
			int c = (*pq.begin()).s;
			pq.erase(pq.begin());
			for(pi i : graph[t][c]){
				if(d[t][c] + i.s < d[t][i.f]){
					pq.erase({d[t][i.f], i.f});
					d[t][i.f] = d[t][c] + i.s;
					pq.insert({d[t][i.f], i.f});
				}
			}
		}
	}
	
	for(int i = 1; i <= n; i++)
	for(pi j : graph[0][i]){
		if(d[0][i] + d[1][j.f] + j.s == d[1][1]) g[i].push_back(j.f);
	}
	
	dfs(1);
	for(int c = t; c >= 1; c--){
		for(int i : rg[c]) sdom[c] = min(sdom[c], sdom[find(i)]);
		if(c > 1) b[sdom[c]].push_back(c);
		for(int i : b[c]){
			int v = find(i);
			if(sdom[i] == sdom[v]) dom[i] = sdom[i];
			else dom[i] = v;
		}
		if(c > 1) unionf(p[c], c);
	}
	for(int c = 2; c <= t; c++) if(dom[c] != sdom[c]) dom[c] = dom[dom[c]];
	
	vector<int> ans;
	for(int c = id[n]; c; c = dom[c]) ans.push_back(rid[c]);
	sort(ans.begin(), ans.end());
	
	cout << ans.size() << endl;
	cout << ans[0];
	for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	cout << endl;
 
	return 0;
}