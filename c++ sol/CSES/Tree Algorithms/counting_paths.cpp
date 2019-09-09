#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n, m;
bool visited[maxn], used[maxn];
int rnk[maxn], prv[maxn], par[maxn], p[maxn];
vector<int> graph[maxn];
vector<pair<int, int>> query[maxn];
int dp[maxn];

int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}

void unionf(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return;
	if(rnk[x] < rnk[y]) swap(x, y);
	if(rnk[x] == rnk[y]) rnk[x]++;
	par[y] = x;
}

void dfs(int c){
	visited[c] = 1;
	par[c] = prv[c] = c;
	
	for(int i : graph[c]){
		if(i == p[c]) continue;
		p[i] = c;
		dfs(i);
		unionf(i, c);
		prv[find(c)] = c;
	}
	
	for(pair<int, int> i : query[c]){
		if(visited[i.first] && !used[i.second]){
			int x = prv[find(i.first)];
			dp[c]++;
			dp[i.first]++;
			dp[x]--;
			if(x) dp[p[x]]--;
			used[i.second] = 1;
		}
	}
}

int dfs2(int c){
	for(int i : graph[c]){
		if(i == p[c]) continue;
		dp[c] += dfs2(i);
	}
	
	return dp[c];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 1; i < n; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		query[a].push_back({b, i});
		query[b].push_back({a, i});
	}
	
	p[0] = -1;
	dfs(0);
	dfs2(0);
	
	cout << dp[0];
	for(int i = 1; i < n; i++) cout << " " << dp[i];
	cout << endl;

	return 0;
}