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
 
const int mxn = 200000, k = 19;
int n, m, q;
int a[mxn], d[mxn], vis[mxn], id[mxn];
int s[k][mxn << 1];
vector<int> g[mxn];
int f[2];
int ans[mxn][2];
 
void dfs(int c, int p){
	id[c] = m, s[0][m++] = d[c];
	for(int i : g[c]) if(i != p){
		d[i] = d[c] + 1;
		dfs(i, c);
		s[0][m++] = d[c];
	}
}
 
pi dfs2(int c, int p){
	pi ret = {0, vis[c] ? -1 : c};
	for(int i : g[c]) if(i != p){
		pi p = dfs2(i, c);
		p.f += !!~p.s;
		ret = max(ret, p);
	}
	return ret;
}
 
int dst(int x, int y){
	int ret = d[x] + d[y];
	x = id[x], y = id[y];
	if(x > y) swap(x, y);
	int z = __lg(y - x + 1);
	ret -= 2 * min(s[z][x], s[z][y - (1 << z) + 1]);
	return ret;
}
 
void sol(int x){
	for(int i = !x * (q - 1); i >= !x && i < q; i += 2 * x - 1){
		int ret = 0;
		if(!~f[0]){
			f[0] = f[1] = a[i];
		}else{
			ret = ans[i - x][x];
			int d0 = dst(f[0], a[i]), d1 = dst(f[1], a[i]);
			if(d0 > d1 && d0 > ret) f[1] = a[i], ret = d0;
			else if(d1 >= d0 && d1 > ret) f[0] = a[i], ret = d1;
		}
		ans[i - !x][x] = ret;
	}
}
 
int main(){
	freopen("maxdist.in", "r", stdin);
	freopen("maxdist.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(0, -1);
	
	for(int i = 1; i < k; i++)
	for(int j = 0; j + (1 << i) <= m; j++){
		s[i][j] = min(s[i - 1][j], s[i - 1][j + (1 << (i - 1))]);
	}
	
	for(int i = 0; i < q; i++){
		cin >> a[i];
		vis[--a[i]] = 1;
	}
	
	f[0] = -1;
	sol(1);
	
	f[0] = dfs2(0, -1).s;
	if(~f[0]){
		pi p = dfs2(f[0], -1);
		f[1] = p.s, ans[q - 1][0] = p.f;
	}
	
	sol(0);
	
	for(int i = 0; i < q; i++) cout << ans[i][0] << " " << ans[i][1] << endl;
 
	return 0;
}