#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200000, k = 18;
int n, m;
int a[maxn], d[maxn], lc[maxn], id[maxn];
int p[k][maxn];
bool used[maxn];
vector<int> graph[maxn], scc[maxn];
vector<int> g[2][maxn];
stack<int> stk;
int s;

void dfs(int c){
	for(int i : graph[c]){
		if(i == p[0][c]) continue;
		d[i] = d[c] + 1;
		p[0][i] = c;
		dfs(i);
	}
}

void dfs2(int c, int t){
	used[c] = !t;
	for(int i : g[t][c]){
		if(used[i] ^ t) continue;
		dfs2(i, t);
	}
	if(t) scc[s].push_back(c), id[c] = s;
	else stk.push(c);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(0);
	
	for(int i = 1; i < k; i++)
	for(int j = 0; j < n; j++){
		p[i][j] = p[i - 1][j] == -1 ? -1 : p[i - 1][p[i - 1][j]];
	}
	
	for(int i = 0; i < m; i++) lc[i] = -1;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
		if(lc[a[i]] == -1){
			lc[a[i]] = i;
		}else{
			int x = lc[a[i]], y = i;
			if(d[x] < d[y]) swap(x, y);
			for(int j = k - 1; j >= 0; j--) if(p[j][x] != -1 && d[p[j][x]] >= d[y]) x = p[j][x];
			for(int j = k - 1; j >= 0; j--) if(p[j][x] != p[j][y]) x = p[j][x], y = p[j][y];
			lc[a[i]] = x == y ? x : p[0][x];
		}
	}
	
	for(int i = 0; i < n; i++){
		if(i != lc[a[i]] && a[p[0][i]] != a[i]){
			g[0][a[p[0][i]]].push_back(a[i]);
			g[1][a[i]].push_back(a[p[0][i]]);
		}
	}
	for(int i = 0; i < m; i++)
	for(int t = 0; t < 2; t++){
		sort(g[t][i].begin(), g[t][i].end());
		g[t][i].erase(unique(g[t][i].begin(), g[t][i].end()), g[t][i].end());
	}
	
	for(int i = 0; i < m; i++) if(!used[i]) dfs2(i, 0);
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		if(used[c]) dfs2(c, 1), s++;
	}
	
	int ret = m;
	for(int i = 0; i < s; i++){
		bool t = 1;
		for(int j : scc[i])
		for(int l : g[1][j]){
			t &= id[l] == i;
		}
		if(t) ret = min(ret, (int)scc[i].size() - 1);
	}
	
	cout << ret << endl;

	return 0;
}