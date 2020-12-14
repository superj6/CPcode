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
 
const int maxn = 1000000;
int n, m, k;
int a[maxn], d[maxn], dp[maxn];
vector<int> graph[maxn];
vector<pi> v;
 
void dfs(int c, int p){
	pi ret;
 	for(int i : graph[c]){
		if(i == p) continue;
		if(~p) dp[i] += dp[c] + graph[c].size() - 2;
		dfs(i, c);
		a[c] |= a[i];
		ret.s = max(ret.s, dp[i]);
		if(ret.s > ret.f) swap(ret.f, ret.s);
	}
	if(graph[c].size() > 2) dp[c] = ret.s;
	dp[c] += graph[c].size() > 1;
}
 
void dfs2(int c, int p){
	if(c == m) return;
	for(int i : graph[c]){
		if(i == p) continue;
		d[i] = d[c] + 1;
		dfs2(i, c);
		if(a[c] && !a[i]) v.push_back({d[i], dp[i] + (c == k)});
	}
}
 
bool works(int x){
	int ret = 0;
	for(pi i : v){
		if(ret > i.f) return 0;
		ret += (i.s + ret) > x;
	}
	return ret <= x;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	m--, k--;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	a[k] = 1, d[k] = -1;
	dfs(m, -1);
	dfs2(k, -1);
	
	sort(v.begin(), v.end());
	
	int l = -1, r = n;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(works(mid)) r = mid;
		else l = mid;
	}
	
	cout << r << endl;
	
	return 0;
}