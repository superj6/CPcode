#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
#define pb push_back

const int maxn = 100001;
struct BIT{
	int bit[maxn];
	
	void clr(int x){
		x++;
		memset(bit, 0, sizeof(int) * x);
	}
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
	
	int qry(int x){
		int ret = 0;
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n;
int col[maxn], hd[maxn], p[maxn], sz[maxn], d[maxn];
pi e[maxn];
vector<int> graph[maxn];
vector<pi> cur[maxn];
BIT bit;

int dfs(int c){
	sz[c] = 1;
	for(int i : graph[c]){
		d[i] = d[c] + 1;
		sz[c] += dfs(i);
	}
	return sz[c];
}

void hld(int c){
	if(graph[c].empty()) return;
	int b = graph[c][0];
	for(int i : graph[c]) if(sz[i] > sz[b]) b = i;
	for(int i : graph[c]){
		hd[i] = (i == b ? hd[c] : i);
		hld(i);
	}
}

int solve(int a, int b){
	vector<int> id;
	vector<pi> val, tmp;
	while(a != -1){
		int c = d[a] - d[hd[a]] + 1;
		tmp.clear();
		for(int i = cur[hd[a]].size() - 1; i >= 0; i--){
			if(cur[hd[a]][i].s < c){
				tmp.pb(cur[hd[a]][i]);
				c -= cur[hd[a]][i].s;
			}else{
				tmp.pb({cur[hd[a]][i].f, c});
				break;
			}
		}
		reverse(tmp.begin(), tmp.end());
		for(pi i : tmp) val.pb(i), id.pb(i.first);
		a = p[hd[a]];
	}
	sort(id.begin(), id.end());
	id.erase(unique(id.begin(), id.end()), id.end());
	bit.clr(id.size());
	int ret = 0;
	for(pi i : val){
		int j = lower_bound(id.begin(), id.end(), i.f) - id.begin();
		ret += i.s * bit.qry(j - 1);
		bit.add(j, i.s);
	}
	int bcol = col[b];
	while(b != -1){
		int c = d[b] - d[hd[b]] + 1;
		while(!cur[hd[b]].empty()){
			if(cur[hd[b]].back().s <= c){
				c -= cur[hd[b]].back().s;
				cur[hd[b]].pop_back();
			}else{
				cur[hd[b]].back().s -= c;
				break;
			}
		}
		cur[hd[b]].pb({bcol, d[b] - d[hd[b]] + 1});
		b = p[hd[b]];
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> col[i];
	p[0] = -1;
	for(int i = 0; i < n - 1; i++){
		cin >> e[i].f >> e[i].s;
		e[i].f--, e[i].s--;
		graph[e[i].f].pb(e[i].s);
		p[e[i].s] = e[i].f;
	}
	
	dfs(0), hld(0);
	cur[0].pb({col[0], 1});
	for(int i = 0; i < n - 1; i++) cout << solve(e[i].f, e[i].s) << endl;;

	return 0;
}