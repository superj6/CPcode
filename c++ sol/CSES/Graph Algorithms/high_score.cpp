#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

const long inf = 50000000000007;
int n, m;
int cnt[2500];
bool visited[2500];
vector<pair<int, long>> graph[2500], rgraph[2500];

void dfs(int c){
	cnt[c]++;
	visited[c] = 1;
	for(int i = 0; i < graph[c].size(); i++){
		if(visited[graph[c][i].first]) continue;
		dfs(graph[c][i].first);
	}
}

void rdfs(int c){
	cnt[c]++;
	visited[c] = 1;
	for(int i = 0; i < rgraph[c].size(); i++){
		if(visited[rgraph[c][i].first]) continue;
		rdfs(rgraph[c][i].first);
	}
}

long bf(){
	long dist[n];
	for(int i = 0; i < n; i++) dist[i] = inf;
	dist[0] = 0;
	
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n; j++){
			if(cnt[j] != 2) continue;
			for(int k = 0; k < graph[j].size(); k++){
				long u = j, v = graph[j][k].first, w = graph[j][k].second;
				if(cnt[v] != 2) continue;
				
				dist[v] = min(dist[v], dist[u] + w);
			}
		}
	}
	
	for(int j = 0; j < n; j++){
		if(cnt[j] != 2) continue;
		for(int k = 0; k < graph[j].size(); k++){
			long u = j, v = graph[j][k].first, w = graph[j][k].second;
			if(cnt[v] != 2) continue;
				
			if(dist[u] + w < dist[v]) return -1;
		}
	}
	
	return -dist[n - 1];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		long a, b, x;
		cin >> a >> b >> x;
		a--, b--;
		graph[a].push_back(make_pair(b, -x));
		rgraph[b].push_back(make_pair(a, -x));
	}
	
	dfs(0);
	memset(visited, 0, sizeof(visited));
	rdfs(n - 1);
	
	cout << bf() << endl;
	
	return 0;
}