/*
This is code of SuperJ6 for Codeforces.
Don't copy my code during f*kin' contests.

2.71828182845904523536
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n, q;
bool visited[maxn];
int rnk[maxn], prv[maxn], par[maxn], p[maxn];
vector<int> graph[maxn];
vector<pair<int, int>> query[maxn];
int ans[maxn];

int find(int x){
	return x == par[x] ? x : find(par[x]);
}

void unionf(int x, int y){
	if(rnk[x] < rnk[y]) swap(x, y);
	if(rnk[x] == rnk[y]) rnk[x]++;
	par[y] = x;
}

void dfs(int c){
	visited[c] = 1;
	par[c] = prv[c] = c;
	for(int i : graph[c]){
		p[i] = c;
		dfs(i);
		unionf(i, c);
		prv[find(c)] = c;
	}
	
	for(pair<int, int> i : query[c]){
		if(visited[i.first]){
			ans[i.second] = prv[find(i.first)] + 1;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 1; i < n; i++){
		int e;
		cin >> e;
		e--;
		graph[e].push_back(i);
	}
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		query[a].push_back({b, i});
		query[b].push_back({a, i});
	}
	
	p[0] = 0;
	dfs(0);
	
	for(int i = 0; i < q; i++) cout << ans[i] << endl;

	return 0;
}