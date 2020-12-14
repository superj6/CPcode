#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 100000;
int n, m;
int par[maxn];
long long sz[maxn];
set<int> ei[maxn];
set<pi> eo[maxn];
long long ret;
 
int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}
 
void solve(int u, int v){
	int x = find(u), y = find(v);
	if(x == y) return;
	auto it = eo[y].lower_bound({x, 0});
	if(it != eo[y].end() && (*it).f == x){
		if(ei[x].size() + eo[x].size() < ei[y].size() + eo[y].size()) swap(x, y);
		vector<pi> vo;
		for(pi i : eo[y]){
			ret -= sz[i.f];
			ei[i.f].erase(i.s);
			if(i.f != x) vo.push_back(i);
		}
		eo[y].clear();
		ret += sz[y] * (2 * sz[x] + ei[x].size() - ei[y].size());
		vector<int> vi;
		for(int i : ei[y]){
			int j = find(i);
			eo[j].erase({y, i});
			if(j != x) vi.push_back(i);
		}
		ei[y].clear();
		par[y] = x, sz[x] += sz[y];
		for(int i : vi) solve(i, x);
		for(pi i : vo) solve(i.s, i.f);
	}else if(!ei[y].count(u)){
		ret += sz[y];
		ei[y].insert(u);
		eo[x].insert({y, u});
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) par[i] = i, sz[i] = 1;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		solve(u, v);
		cout << ret << endl;
	}
 
	return 0;
}