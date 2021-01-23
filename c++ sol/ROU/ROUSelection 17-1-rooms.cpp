/*
	Realize there are a relatively small number of queries. This means you can divide queries into two parts,
finding regions completely contained within a query, or a region that intersects the boundary of a query. The first
part can be solved with cdq, a specific form of divide and conquer, and a 2d bit. You split rectangles based on there
bottom edge and sort by there leftmost edge, then query for points based on the the upper right area of the rectangle.
the second part can be solved by naive traversal along the boundary keeping track of which sections have been added.
The time complexity is O(n * q + (n * m + q) * lg^3 n).
	However, a better solution I didn't realize exists. Instead, just do a 2d prefix sum of each regions bottom
left most point. Now you can just naively query leftmost points within a rectangle, and the only regions not added
will only interset with the bottom and leftmost side. The time complexity of this is just O(n * (m + q))
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<pi, pi>
#define f first
#define s second
#define vi vector<int>

const int mxn = 2001, mxq = 5000, mxk = mxn * mxn + mxq, w = 4;
const int dx[w] = {1, 0, -1, 0};
const int dy[w] = {0, 1, 0, -1};
int n, m, k, q;
int a[mxn][mxn], f[mxn][mxn], bit[mxn][mxn];
int lx[mxk], rx[mxk], ly[mxk], ry[mxk], vis[mxk], dp[mxq];
vi vv[mxn];
auto cmp = [](int x, int y){ return ly[x] == ly[y] ? x > y : ly[x] > ly[y];};

void add(int x, int y, int z){
	for(int i = x + 1; i <= n; i += i & -i)
	for(int j = y + 1; j <= m; j += j & -j){
		bit[i][j] += z;
	}
}

int qry(int x, int y){
	int ret = 0;
	for(int i = x + 1; i; i -= i & -i)
	for(int j = y + 1; j; j -= j & -j){
		ret += bit[i][j];
	}
	return ret;
}

void dfs(int x, int y){
	f[x][y] = k;
	lx[k] = min(lx[k], x), ly[k] = min(ly[k], y);
	rx[k] = max(rx[k], x), ry[k] = max(ry[k], y);
	for(int i = 0; i < w; i++){
		int xx = x + dx[i], yy = y + dy[i];
		if(xx >= 0 && xx < n && yy >= 0 && yy < m && !~f[xx][yy] && a[x][y] == a[xx][yy]){
			dfs(xx, yy);
		} 
	}
}

vi sol(int l, int r){
	vi v;
	int mid = (l + r) / 2;
	if(l == r){
		v = vv[l];
		sort(v.begin(), v.end(), cmp);
	}else{
		vi vl = sol(l, mid), vr = sol(mid + 1, r);
		v.resize(vl.size() + vr.size());
		merge(vl.begin(), vl.end(), vr.begin(), vr.end(), v.begin(), cmp);
	}
	for(int i : v){
		if(i < q && (l == r || lx[i] <= mid)) dp[i] += qry(rx[i], ry[i]);
		if(i >= q && (l == r || lx[i] > mid)) add(rx[i], ry[i], 1);
	}
	for(int i : v) if(i >= q && (l == r || lx[i] > mid)) add(rx[i], ry[i], -1);
	return v;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		char c;
		cin >> c;
		a[i][j] = c - 'a', f[i][j] = -1;
	}
	
	cin >> q;
	k = q;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		if(!~f[i][j]){
			lx[k] = ly[k] = max(n, m);
			rx[k] = ry[k] = -1;
			dfs(i, j), k++;
		}
	}
	
	for(int i = 0; i < q; i++){
		cin >> lx[i] >> ly[i] >> rx[i] >> ry[i];
		lx[i]--, ly[i]--, rx[i]--, ry[i]--;
		for(int j = lx[i]; j <= rx[i]; j++){
			if(ly[i] && f[j][ly[i]] == f[j][ly[i] - 1] && !vis[f[j][ly[i]]]){
				dp[i]++, vis[f[j][ly[i]]] = 1;
			}
			if(ry[i] < m && f[j][ry[i]] == f[j][ry[i] + 1] && !vis[f[j][ry[i]]]){
				dp[i]++, vis[f[j][ry[i]]] = 1;
			}
		}
		for(int j = ly[i]; j <= ry[i]; j++){
			if(lx[i] && f[lx[i]][j] == f[lx[i] - 1][j] && !vis[f[lx[i]][j]]){
				dp[i]++, vis[f[lx[i]][j]] = 1;
			}
			if(rx[i] < n && f[rx[i]][j] == f[rx[i] + 1][j] && !vis[f[rx[i]][j]]){
				dp[i]++, vis[f[rx[i]][j]] = 1;
			}
		}
		for(int j = lx[i]; j <= rx[i]; j++) vis[f[j][ly[i]]] = vis[f[j][ry[i]]] = 0;
		for(int j = ly[i]; j <= ry[i]; j++) vis[f[lx[i]][j]] = vis[f[rx[i]][j]] = 0;
	}
	
	for(int i = 0; i < k; i++) vv[lx[i]].push_back(i);
	
	sol(0, n - 1);
	
	for(int i = 0; i < q; i++) cout << dp[i] << endl;
	
	return 0;
}