#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200000;
int n, m;
int par[maxn];
vector<int> graph[maxn];
queue<int> q;
int ans[maxn];

int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}

int main(){
	freopen("fcolor.in", "r", stdin);
	freopen("fcolor.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
	}
	
	for(int i = 0; i < n; i++){
		par[i] = i;
		if(graph[i].size() >= 2) q.push(i);
	} 
	
	while(!q.empty()){
		int c = q.front();
		if(graph[c].size() < 2){
			q.pop();
		}else{
			int x = find(graph[c].back());
			graph[c].pop_back();
			int y = find(graph[c].back());
			if(x == y) continue;;
			if(graph[x].size() < graph[y].size()) swap(x, y);
			par[y] = x;
			graph[x].insert(graph[x].end(), graph[y].begin(), graph[y].end());
			q.push(x);
		}
	}
	
	
	int ret = 0;
	for(int i = 0; i < n; i++){
		int x = find(i);
		if(!ans[x]) ans[x] = ++ret;
		cout << ans[x] << endl;
	}

	return 0;
}