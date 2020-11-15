/*
  First compress to scc since every node in a single scc functions the same so you can solve problem on a dag. Now you have to go both
forward and backward in topological order of the dag and keep track of how many nodes don't have a parent. The only way a node can reach
all nodes below it in topological order is if every node after it in topoligical order has a parent, since that means each node has to
be reached by one before it and it is the first node of the topo suffix set. If another node doesn't have a parent after it, that means
it would be unreachable to the current one. When you try this for both forward and backward topo order, every node in the dag that can
reach all the ones before it on reverse edges and all the ones after it on forward edges satisfies the condition of the problem.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500000;
int n, m, k;
int a[mxn], f[mxn], sc[mxn], vis[mxn];
vector<int> v;
vector<int> g[2][mxn], gr[2][mxn];
stack<int> stk;

void dfs(int c, int t){
	vis[c] = !t;
	for(int i : g[t][c]) if(vis[i] == t) dfs(i, t);
	if(!t) stk.push(c);
	else sc[c] = k;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[0][u].push_back(v);
		g[1][v].push_back(u);
	}
	
	for(int i = 0; i < n; i++) if(!vis[i]) dfs(i, 0);
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		if(vis[c]) dfs(c, 1), k++;
	}
	
	for(int t = 0; t < 2; t++)
	for(int i = 0; i < n; i++)
	for(int j : g[t][i]){
		if(sc[i] != sc[j]) gr[t][sc[i]].push_back(sc[j]);
	}
	
	for(int t = 0; t < 2; t++, memset(a, 0, sizeof(a)))
	for(int i = !t * (k - 1), j = 0; i >= 0 && i < k; i += 2 * t - 1, j++){
		sort(gr[t][i].begin(), gr[t][i].end());
		gr[t][i].erase(unique(gr[t][i].begin(), gr[t][i].end()), gr[t][i].end());
		for(int l : gr[t][i]) j -= !a[l], a[l] = 1;
		f[i] += !j;
	}
	
	for(int i = 0; i < n; i++) if(f[sc[i]] == 2) v.push_back(i + 1);
	
	cout << v.size() << endl;
	if(!v.empty()) cout << v[0];
	for(int i = 1; i < v.size(); i++) cout << " " << v[i];
	cout << endl;

	return 0;
}
