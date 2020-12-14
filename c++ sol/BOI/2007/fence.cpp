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