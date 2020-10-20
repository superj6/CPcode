/*
  Once you efficiently turn the rectangles into a graph, it just becomes a shortest path problem. To do this, you can use coordinate
compression to create a grid and create all edges between adjacent points in the grid, since this will make sure to get every important
straight path while also only having O(k^2) edges. Now for each point in the graph, mark whether it is completely inside a rectangle. To
make sure there is at least one point inside each rectangle, I double the coordinates and add a new point inside each rectangle. Now
the reachable nodes in the graph are just the nodes not within any rectangle, and they can travel to any adjacent reachable node with
edge length of the difference in their original coordinates. Now you just need to run dijkstra from each rectangle corner, however, to
ensure that the path goes in a loop around the first rectangle, create a second state for the grid which is whether the path has currently
crossed over the line between one of the first rectangle's vertices going outward to infinity, and then when you run dijkstra you can just
test if the shortest path that has crossed over that line and has landed back at the original point is the best, since any loop must cross
over the line an odd amount of times.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

pi operator*(int x, pi p){
	return {x * p.f, x * p.s};
}

const int mxn = 600, w = 4;
const pi di[w] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m, k;
pi a[mxn][2];
int idx[mxn], idy[mxn];
int g[mxn][mxn], d[mxn][mxn], vis[mxn][mxn];
auto cmp = [](pi x, pi y){ return d[x.f][x.s] > d[y.f][y.s];};
priority_queue<pi, vector<pi>, decltype(cmp)> pq(cmp);

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k;
	
	for(int i = 0; i < k; i++)
	for(int j = 0; j < 2; j++){
		cin >> a[i][j].f >> a[i][j].s;
		a[i][j] = 2 * a[i][j];
		for(int l = 0; l <= j; l++){
			idx[n++] = a[i][j].f - l, idy[m++] = a[i][j].s - l;
		}
	}
	
	sort(idx, idx + n);
	sort(idy, idy + m);
	n = unique(idx, idx + n) - idx;
	m = unique(idy, idy + m) - idy;
	
	for(int i = 0; i < k; i++)
	for(int j = 0; j < 2; j++){
		a[i][j].f = lower_bound(idx, idx + n, a[i][j].f) - idx;
		a[i][j].s = lower_bound(idy, idy + m, a[i][j].s) - idy;
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++)
	for(int l = 0; l < k; l++){
		g[i][j] |= a[l][0].f < i && i < a[l][1].f && a[l][0].s < j && j < a[l][1].s;
	}
	
	int ret = 0x3f3f3f3f;
	for(int i = 0; i < k; i++)
	for(int j = 0; j < 2; j++) if(!g[a[i][j].f][a[i][j].s]){
		memset(d, 0x3f, sizeof(d));
		memset(vis, 0, sizeof(vis));
		d[a[i][j].f << 1][a[i][j].s << 1] = 0;
		pq.push(2 * a[i][j]);
		while(!pq.empty()){
			pi c = pq.top();
			pq.pop();
			if(vis[c.f][c.s]) continue;
			vis[c.f][c.s] = 1;
			for(int l = 0; l < w; l++){
				pi p = c + 2 * di[l];
				if(p.f < 0 || p.s < 0 || p.f >= 2 * n || p.s >= 2 * m || g[p.f >> 1][p.s >> 1]) continue;
				if((min(p.f, c.f) >> 1) == a[0][0].f && (max(p.f, c.f) >> 1) == a[0][0].f + 1 && (p.s >> 1) <= a[0][0].s) p.f ^= 1, p.s ^= 1;
				int dd = d[c.f][c.s] + abs(idx[c.f >> 1] - idx[p.f >> 1]) + abs(idy[c.s >> 1] - idy[p.s >> 1]);
				if(dd < d[p.f][p.s]){
					d[p.f][p.s] = dd;
					pq.push(p);
				}
			}
		}
		ret = min(ret, d[a[i][j].f << 1 | 1][a[i][j].s << 1 | 1]);
	}
	ret >>= 1;
	
	cout << ret << endl;

	return 0;
}
