/*
	This problem was confusing due to stupid wording, but essentially you need to place a tree within a square such that you
draw up to two rectangles to only contain the points on the path between two given points, and no more. This obviously means we
need to be able to draw a single rectangle from a point to any of its parents such that it only contains the points on the path
to its parents and no more, because then we can just compute lca for general paths. A good technique when dealing with a problem
like this is to think how to do it recursively. If it is possible to build a tree of n nodes in a square of sidelength n, it should
be possible to do it for any size less than it. This leads to the recursive solution of placing the root of the tree in the top 
right corner, then dividing the remaining subtrees into boxes along the diagonal of the original square based on their original
size. Because you orient them along the diagonal, if you are careful, you should make it so no subbox is intersecting in horizontal
or vertical coordinates. This mean that each can be reached from the root without touching the others, so you can make the rectangle
from a node along the path to any of its ancestors as desired. The complexity is O((n + q)logn) due to calculating lca.
*/

#include "grader.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 100000, k = 18;
int n, q;
int x[maxn], y[maxn];
int sz[maxn], dist[maxn];
int par[k][maxn];
vector<int> graph[maxn];

/*
void setFarmLocation(int id, int x, int y){
	cout << id << " " << x << " " << y << endl;
}

void addBox(int x, int y, int X, int Y){
	cout << x << " " << y << " " << X << " " << Y << endl;
}
*/

int dfs(int c){
	sz[c] = 1;
	for(int i : graph[c]){
		if(i == par[0][c]) continue;
		par[0][i] = c;
		dist[i] = dist[c] + 1;
		sz[c] += dfs(i);
	}
	return sz[c];
}

void dfs2(int c, int l){
	x[c] = l + 1, y[c] = l + sz[c];
	setFarmLocation(c, x[c], y[c]);
	for(int i : graph[c]){
		if(i == par[0][c]) continue;
		dfs2(i, l);
		l += sz[i];
	}
}

void addRoad(int a, int b){
	graph[a].push_back(b);
	graph[b].push_back(a);
}

void buildFarms(){
	par[0][0] = -1;
	n = dfs(0);
	dfs2(0, 0);

	for(int i = 1; i < k; i++){
		for(int j = 0; j < n; j++){
			par[i][j] = par[i - 1][j] == -1 ? -1 : par[i - 1][par[i - 1][j]];
		}
	}
}

void notifyFJ(int a, int b){
	if(dist[a] < dist[b]) swap(a, b);
	
	int c = a, d = b;
	for(int i = k - 1; i >= 0; i--){
		if(par[i][c] != -1 && dist[par[i][c]] >= dist[d]) c = par[i][c];
	}
	
	if(c == d){
		addBox(min(x[a], x[b]), min(y[a], y[b]), max(x[a], x[b]), max(y[a], y[b]));
		return;
	}
	
	for(int i = k - 1; i >= 0; i--){
		if(par[i][c] != par[i][d]){
			c = par[i][c];
			d = par[i][d];
		}
	}
	d = par[0][d];
	
	addBox(min(x[a], x[c]), min(y[a], y[c]), max(x[a], x[c]), max(y[a], y[c]));
	addBox(min(x[b], x[d]), min(y[b], y[d]), max(x[b], x[d]), max(y[b], y[d]));
}

/*
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		addRoad(a, b);
	}
	
	buildFarms();
	cout << endl;
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		notifyFJ(a, b);
	}
	
	return 0;
}
*/
