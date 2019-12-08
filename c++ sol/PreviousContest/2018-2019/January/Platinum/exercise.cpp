/*
	The problem asks to count the number of cycles using two nonstandard edges with the rest of the tree's edges.
Obviously, each pair of edges can be used at most once to form a cycle. To start, for each of the nonstandard edges, decompose
them into two segments of the tree from each of the nodes on it to their lca. Now, the problem decomposes to find the number of
such segments that intersect, as any two pair of nonstadard edges that intersect between their nodes and their lca can form
exactly one edge. However, you have to be sure to subtract overcounting when two nonstadard edges have the same lca. To count
the number of pairs of segments on a tree that intersect, begin by finding for each node on a nonstandard edge the node that
connects right below the lca. Add one to the value of this node. Then you are going to run dfs to compute the prefix sum going
down the tree and add to the result the prefix sum of each node on each standard edge and subtract the prefix sum from the lca.
This will count the number of nodes that are on each segment of the tree you split the nonstandard edges into. However, when two
nodes of different nonstandard edges connect to the same lca, you will count as the tree segments intersecting twice, so you need
to subtract the amount of pairs that connect to the same node below the lca. The complexity of this is O(mlogn) due binary
lifting for the lca.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'

const int maxn = 200000, k = 19;
int n, m;
int p[maxn][k];
int dist[maxn], amt[maxn], x[maxn], y[maxn], l[maxn];
map<pair<int, int>, int> cnt;
vector<int> graph[maxn];

void dfs1(int c){
	for(int i : graph[c]){
		if(i == p[c][0]) continue;
		p[i][0] = c;
		dist[i] = dist[c] + 1;
		dfs1(i);
	}
}

void dfs2(int c){
	for(int i : graph[c]){
		if(i == p[c][0]) continue;
		amt[i] += amt[c];
		dfs2(i);
	}
}

void genp(){
	for(int j = 1; j < k; j++){
		for(int i = 0; i < n; i++){
			p[i][j] = p[i][j - 1] == -1 ? -1 : p[p[i][j - 1]][j - 1];
		}
	}
}

int lca(int a, int b){
	for(int i = k - 1; i >= 0; i--){
		if(p[a][i] != -1 && dist[b] <= dist[p[a][i]]) a = p[a][i];
		if(p[b][i] != -1 && dist[a] <= dist[p[b][i]]) b = p[b][i];	
	} 
	for(int i = k - 1; i >= 0; i--){
		if(p[a][i] != -1 && p[b][i] != -1 && p[a][i] != p[b][i]){
			a = p[a][i];
			b = p[b][i];
		}
	} 
	return a == b ? a : p[a][0];
}

int top(int a, int b){
	if(a == b) return -1;
	for(int i = k - 1; i >= 0; i--){
		if(p[a][i] != -1 && dist[b] < dist[p[a][i]]) a = p[a][i];
	} 
	return a;
}

int main(){
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	m -= n - 1;
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	p[0][0] = -1;
	dist[0] = 0;
	dfs1(0);
	genp();
	
	long ans = 0;
	for(int i = 0; i < m; i++){
		cin >> x[i] >> y[i];

		x[i]--, y[i]--;
		l[i] = lca(x[i], y[i]);
		
		int nx = top(x[i], l[i]), ny = top(y[i], l[i]);
		if(nx > ny) swap(nx, ny);
		
		if(nx != -1) ans -= ++amt[nx];
		if(ny != -1) ans -= ++amt[ny];
		if(nx != -1 && ny != -1) ans -= cnt[{nx, ny}]++;
	}
	
	dfs2(0);
	
	for(int i = 0; i < m; i++){
		ans += amt[x[i]] + amt[y[i]] - 2 * amt[l[i]];
	}
	
	cout << ans << endl;

	return 0;
}
