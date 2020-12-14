/*
  NAME: super_j6
  LANG: C++
  PROG: solder
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const ll inf = 0x3f3f3f3f3f3f3f3f;

struct ln{
	mutable ll k, m, p;
	bool operator<(const ln& x) const{ return k > x.k;}
	bool operator<(ll x) const{ return p < x;}
};

struct cht : multiset<ln, less<>> {
	ll lzy = 0;
	ll div(ll a, ll b){ return a / b - (a ^ b < 0 && a % b);}
	
	bool isect(iterator x, iterator y){
		if(y == end()){
			x->p = inf;
			return 0;
		}
		if(x->k == y->k) x->p = (2 * (x->m < y->m) - 1) * inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	
	void add(ll k, ll m){
		auto z = insert({k, m - lzy, 0}), y = z++, x = y;
		while(isect(y, z)) z = erase(z);
		if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	
	void addl(ll x){
		lzy += x;
	}
	
	ll qry(ll x){
		if(empty()) return inf;
		ln l = *lower_bound(x);
		return l.k * x + l.m + lzy;
	}
};

ll sq(ll x){
	return x * x;
}

const int maxn = 50000;
int n;
int d[maxn], sz[maxn];
cht dp[maxn];
vector<int> graph[maxn];

void dfs(int c, int p){
	int h = -1;
	ll ret1 = -sq(d[c]), ret2 = inf;
	sz[c] = 1;
	for(int i : graph[c]){
		if(i == p) continue;   
		d[i] = d[c] + 1;
		dfs(i, c);
		sz[c] += sz[i];
		if(!~h || sz[i] > sz[h]) h = i;
		ll x = dp[i].qry(d[c]);
		ret1 += x + sq(d[c]);
		dp[i].addl(-x);
	}
	
	if(!~h){ 
		dp[c].add(-2 * d[c], sq(d[c]));
		return;
	}
	
	swap(dp[h], dp[c]);
	
	for(int i : graph[c]){
		if(i == p || i == h) continue;
		for(ln l : dp[i]){
			ret2 = min(ret2, 2 * d[c] * l.k + l.m + dp[i].lzy +
				dp[c].qry(l.k / 2 + 2 * d[c]));
		}
		for(ln l : dp[i]) dp[c].add(l.k, l.m + dp[i].lzy);
	}
	
	if(ret2 < inf) dp[c].add(-2 * d[c], ret2 + 4 * sq(d[c]));
	dp[c].addl(ret1);
}

int main(){
	freopen("solder.in", "r", stdin);
	freopen("solder.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(0, -1);
	
	if(!~-graph[0].size()) cout << dp[0].qry(0) << endl;
	else for(ln l : dp[0]) if(!l.k) cout << (l.m + dp[0].lzy) << endl;

	return 0;
}