#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;
#define endl '\n'
 
const int maxn = 200000;
int n, q;
int scc[maxn], tre[maxn], ind[maxn];
bool used[maxn];
vector<int> graph[2][maxn];
vector<int> cycle[maxn], tree[maxn];
int par[maxn], dep[maxn], hev[maxn], hed[maxn], pos[maxn];
stack<int> stk;
int s = 0, p = 0;
 
void dfs(int c, int x){
	used[c] = 1;
	for(int i : graph[x][c]){
		if(!used[i]) dfs(i, x);
	}
	
	if(!x){
		stk.push(c);
	}else{
		scc[c] = s;
		ind[c] = cycle[s].size();
		cycle[s].push_back(c);
	}
}
 
int dfs2(int c){
	tre[c] = p;
	int sz = 1, misz = 0;
	for(int i : graph[1][c]){
		if(i == par[c] || scc[i] == scc[c]) continue;
		
		par[i] = c, dep[i] = dep[c] + 1;
		int isz = dfs2(i);
		sz += isz;
		
		if(isz > misz) misz = isz, hev[c] = i;
	}
	return sz;
}
 
void decomp(int c, int h){
	hed[c] = h, pos[c] = tree[p].size(), tree[p].push_back(c);
	if(hev[c] != -1) decomp(hev[c], h);
	for(int i : graph[1][c]){
		if(par[c] == i || hev[c] == i || scc[i] == scc[c]) continue;
		decomp(i, i);
	}
}
 
void ans(){
	int a, b;
	cin >> a >> b;
	a--, b--;
	
	int dist;
	
	if(tre[a] == tre[b]){
		dist = dep[a] - dep[b];
		while(a != -1 && hed[a] != hed[b] && dep[a] > dep[b]) a = par[hed[a]];
		if(a == -1 || hed[a] != hed[b] || dep[a] < dep[b]) dist = -1;
	}else{
		dist = dep[a];
		a = tree[tre[a]][0];
		
		int m = cycle[scc[a]].size();
		if(scc[a] == scc[b]) dist += (ind[b] - ind[a] + m) % m;
		else dist = -1;
	}
	
	cout << dist << endl;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		graph[0][i].push_back(x);
		graph[1][x].push_back(i);
	}
	
	for(int i = 0; i < n; i++){
		if(!used[i]) dfs(i, 0);
	}
	
	memset(used, 0, sizeof(used));
	
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		
		if(used[c]) continue;
		dfs(c, 1);
		s++;
	}
	
	memset(hev, -1, sizeof(hev));
	
	for(int i = 0; i < n; i++){
		if(cycle[scc[i]].size() == 1 && graph[0][i][0] != i) continue;
		par[i] = -1;
		
		dfs2(i);
		decomp(i, i);
		p++;
	}
	
	for(int i = 0; i < q; i++) ans();
 
	return 0;
}