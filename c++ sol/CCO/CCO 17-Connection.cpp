/*
  Create a spanning tree and dfs to compute things for binary lifting. Also hold queries in sets for each of the vertices it corresponds
to. Now add edges 1 by 1, skipping an edge if it is part of the spanning tree or if regions already connected. If they are not connected
compute lca and combine all nodes on the path between them with dsu while merging the query sets small to large. If both vertices of a 
query combine, that query can be answered. This process will merge components when they have at least two paths between them ie they are
a biconnected component, and compress each biconnected component to a single point. If you wanted to combine biconnected components
completely online, just hold two dsu, one for spanning tree and one for biconnected components, and just compute lca by naively traversing
up the tree from both parent pointers simultaneously, which is O(length of cycle) which is the same as merging all nodes to one biconnected
component anyway so does not change complexity.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 150001, k = 18;
int n, m, q;
int u[mxn], v[mxn], d[mxn], pp[mxn], par[mxn];
int p[k][mxn];
set<int> s[mxn];
vector<int> g[mxn];
int ans[mxn];

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

void dfs(int c){
	for(int i = 1; i < k; i++) p[i][c] = ~p[i - 1][c] ? p[i - 1][p[i - 1][c]] : -1;
	for(int i : g[c]){
		if(u[i] == p[0][c]) continue;
		if(u[i] != c) swap(u[i], v[i]);
		d[v[i]] = d[c] + 1, pp[v[i]] = i, p[0][v[i]] = c;
		dfs(v[i]);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	n++;
	
	for(int i = 0; i < n; i++){
		par[i] = i, pp[i] = p[0][i] = -1;
	} 
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i];
		int x = fnd(u[i]), y = fnd(v[i]);
		if(x != y){
			par[y] = x;
			g[u[i]].push_back(i);
			g[v[i]].push_back(i);
		}
	}
	
	for(int i = 0; i < n; i++){
		if(!d[i]) dfs(i);
		par[i] = i;
	} 
	
	for(int i = 0; i < q; i++){
		int x, y;
		cin >> x >> y;
		if(x == y){
			ans[i] = 0;
		}else{
			s[x].insert(i);
			s[y].insert(i);
			ans[i] = -1;
		}
	}
	
	for(int i = 0; i < m; i++){
		int x = fnd(u[i]), y = fnd(v[i]);
		if(pp[v[i]] == i || x == y) continue;
		
		int w = x, z = y;
		if(d[w] < d[z]) swap(w, z);
		for(int j = k - 1; ~j; j--) if(~p[j][w] && d[p[j][w]] >= d[z]) w = p[j][w];
		for(int j = k - 1; ~j; j--) if(p[j][w] != p[j][z]) w = p[j][w], z = p[j][z];
		if(w != z) w = p[0][w];
		w = fnd(w);
		
		int f[2] = {x, y};
		for(int t = 0; t < 2; t++)
		for(y = f[t]; y != w; y = x){
			x = fnd(p[0][y]);
			par[y] = x;
			if(s[x].size() < s[y].size()) swap(s[x], s[y]);
			for(int j : s[y]){
				if(s[x].count(j)){
					ans[j] = i;
					s[x].erase(j);
				}else{
					s[x].insert(j);
				}
			}
			s[y].clear();
		}
	}
	
	for(int i = 0; i < q; i++) cout << ans[i] << endl;

	return 0;
}
