#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n, m;
int d[maxn];
bool used[maxn];
vector<int> graph[maxn], graph2[maxn];
queue<int> q;

int dfs(int c){
	used[c] = 1;
	if(!d[c]) q.push(c);
	int ret = 1;
	for(int i : graph2[c]){
		if(used[i]) continue;
		ret += dfs(i);
	}
	return ret;
}

int solve(int c){
	while(!q.empty()) q.pop();
	int ret = dfs(c);
	for(int i = 0; i < ret; i++){
		if(q.empty()) return ret;
		int c = q.front();
		q.pop();
		for(int i : graph[c]){
			d[i]--;
			if(!d[i]) q.push(i);
		}
	}
	return ret - 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph2[u].push_back(v);
		graph2[v].push_back(u);
		d[v]++;
	}
	
	int ret = 0;
	for(int i = 0; i < n; i++) if(!used[i]) ret += solve(i);
	
	cout << ret << endl;

	return 0;
}