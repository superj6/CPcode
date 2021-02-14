/*
	The most important realization is the tournament graph is composed of many scc tournament subgraphs, and you can reach
every scc after the current one in topological order. Also, every scc has a hamiltonian cycle, so you can reach every node equivalent and after
to the current one in topological order. The hard part of the problem is then finding the hamiltonian cycles within each scc. To do this, you
can hold all scc's with nodes in their cycle order found so far in topological ordering, and add nodes one by one. Let the current node be i.
You first find x which is the first scc in topo order such that it has a node where there is an edge from i to that node, and y which is the
last scc in topo order which has a node where where there is an edge from that node to i. If x < y, since there is a path from x to y, y to i,
and i to x, that forms a new cycle, so it is easy to merge all the cycles between x and y inclusive with i and create a new scc in their place.
Otherwise if x == y, since there is at least one edge in x to i and one edge from i to x, you just need to find two nodes adjacent in x's cycle
such that you can merge i between them. If none of the prior cases are true, then i is it's own new scc, so you add i between scc x and y. Now
it is easy to print each nodes path by just making sure you start the cycle with the starting node, then print all cycles afterwards arbitrarily
as since the graph is a tournament graph and they are in different scc's, every node in the current scc has an edge directed towards every node
in the next scc. The solution is O(n^2).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 2001;
int n;
int a[mxn], b[mxn], dp[mxn];
int g[mxn][mxn];
vector<vector<int>> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < i; j++){
			char c;
			cin >> c;
			g[j][i] = c & 1, g[i][j] = !g[j][i];
		}
		
		int x = v.size(), p = -1, y = -1, q = -1;
		for(int j = 0; j < v.size(); j++)
		for(int l = 0; l < v[j].size(); l++){
			if(x == v.size() && g[i][v[j][l]]) x = j, p = l;
			if(g[v[j][l]][i]) y = j, q = l;
		}
		
		if(x < y){
			rotate(v[x].begin(), v[x].begin() + p, v[x].end());
			rotate(v[y].begin(), v[y].begin() + (q + 1) % v[y].size(), v[y].end());
			for(int j = x + 1; j <= y; j++){
				v[x].insert(v[x].end(), v[j].begin(), v[j].end());
			}
			v.erase(v.begin() + x + 1, v.begin() + y + 1);
			v[x].push_back(i);
		}else if(x == y){
			y = 1;
			while(y < v[x].size() && (!g[v[x][y - 1]][i] || !g[i][v[x][y]])) y++;
			v[x].insert(v[x].begin() + y, i);
		}else{
			v.insert(v.begin() + x, vector<int>(1, i));
		}
	}
	
	for(int i = v.size() - 1; ~i; i--){
		dp[i] = v[i].size() + dp[i + 1];
		for(int j = 0; j < v[i].size(); j++) a[v[i][j]] = i, b[v[i][j]] = j;
	}
	
	for(int t = 0; t < n; t++){
		cout << dp[a[t]];
		for(int i = a[t], j = b[t]; i < v.size(); i++, j = 0)
		for(int l = 0; l < v[i].size(); l++){
			cout << " " << (v[i][(j + l) % v[i].size()] + 1);
		}
		cout << endl;
	}
	
	return 0;
}