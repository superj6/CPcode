#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100001;

struct BIT{
	int bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
	
	int qry(int x){
		int ret = 0;
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
	
	int qry(int a, int b){
		return qry(b) - qry(a - 1);
	}
};

const int w = 18;
int n, m, k;
int l[maxn], r[maxn], d[maxn], dp[maxn];
int p[w][maxn];
vector<pi> graph[maxn];
BIT bit;
vector<int> ans;

auto cmp = [&](int x, int y){
	return (pi){r[x], -l[x]} < (pi){r[y], -l[y]};
};
set<int, decltype(cmp)> a(cmp);
vector<pi> b;

int dfs(int c){
	r[c] = l[c];
	for(pi i : graph[c]){
		if(i.f == p[0][c]) continue;
		d[i.f] = d[c] + 1;
		l[i.f] = r[c] + 1;
		p[0][i.f] = c;
		r[c] = dfs(i.f);
	}
	return r[c];
}

int lca(int x, int y){
	if(d[x] < d[y]) swap(x, y);
	for(int i = w - 1; i >= 0; i--) if(p[i][x] != -1 && d[p[i][x]] >= d[y]) x = p[i][x];
	for(int i = w - 1; i >= 0; i--){
		if(p[i][x] != p[i][y]){
			x = p[i][x];
			y = p[i][y];
		}
	}
	return x == y ? x : p[0][x];
}

void dfs2(int c){
	for(pi i : graph[c]){
		if(i.f == p[0][c]) continue;
		dfs2(i.f);
		if(dp[i.f] >= k) ans.push_back(i.s);
		dp[c] += dp[i.f];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;

	for(int i = 1; i < n; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back({v, i});
		graph[v].push_back({u, i});
	}
	
	p[0][0] = -1;
	dfs(0);
	
	for(int i = 1; i < w; i++)
	for(int j = 0; j < n; j++){
		p[i][j] = p[i - 1][j] == -1 ? -1 : p[i - 1][p[i - 1][j]];
	}
	
	for(int i = 0; i < m; i++){
		int s;
		cin >> s;
		
		b.clear();
		for(int j = 0; j < s; j++){
			int x;
			cin >> x;
			x--;
			a.insert(x);
		}
		while(!a.empty()){
			if(!b.empty()) a.insert(lca(b.back().f, *a.begin()));
			b.push_back({*a.begin(), 0});
			a.erase(a.begin());
			b.back().s = -bit.qry(l[b.back().f], r[b.back().f]) + 1;
			bit.add(l[b.back().f], b.back().s);
			dp[b.back().f] += b.back().s;
		}
		dp[b.back().f]--;
		for(pi i : b){
			bit.add(l[i.f], -i.s);
		}
	}
	
	dfs2(0);
	sort(ans.begin(), ans.end());
	
	cout << ans.size() << endl;
	if(!ans.empty()) cout << ans[0];
	for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}