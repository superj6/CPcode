#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

const int mod = 1000000007;
const int maxn = 100001;
int n;
pi sz[maxn];
int par[maxn], rnk[maxn];
long long f[maxn], rf[maxn], iv[maxn];
vector<pii> a;
vector<int> graph[maxn];
set<int> st;
int rt;
int ans[maxn];

void init(){
	f[0] = f[1] = rf[0] = rf[1] = iv[1] = 1;
	for(int i = 2; i < maxn; i++){
		iv[i] = mod - mod / i * iv[mod % i] % mod;
		f[i] = i * f[i - 1] % mod;
		rf[i] = iv[i] * rf[i - 1] % mod;
	}
}

int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}

void dfs(int c, int d, int p, int pp){
	if(graph[c].size() != 2){
		if(p != -1) a.push_back({d, {c, p}});
		d = 0, p = c;
	}
	for(int i : graph[c]){
		if(i == pp) continue;
		dfs(i, d + 1, p, c);
	}
}

int main(){
	freopen("circus.in", "r", stdin);
	freopen("circus.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	init();
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	while(graph[rt].size() == 2) rt++;
	
	dfs(rt, 0, -1, -1);
	
	for(int i = 0; i < n; i++){
		if(graph[i].size() != 2){
			par[i] = i;
			sz[i].f = graph[i].size();
			st.insert(i);
		}
	}
	
	sort(a.begin(), a.end());
	ans[n - 1] = f[n];
	for(int i = n - 2, j = 0; i >= 0; i--){
		for(; j < a.size() && i < n - a[j].f - 2; j++){
			int x = find(a[j].s.f), y = find(a[j].s.s);
			if(rnk[x] < rnk[y]) swap(x, y);
			rnk[x] += rnk[x] == rnk[y];
			par[y] = x;
			sz[x].f += sz[y].f - 2;
			sz[x].s += sz[y].s + a[j].f;
			st.erase(y);
		}
		ans[i] = f[i + 1];
		for(int j : st) ans[i] = ans[i] * rf[(n - i - 2) * (sz[j].f - 1) + sz[j].s] % mod;
	}
	
	for(int i = 0; i < n; i++) cout << ans[i] << endl;
	
	return 0;
}