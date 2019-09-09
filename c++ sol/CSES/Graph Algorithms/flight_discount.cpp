#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const long inf = 100000000000007;
int n, m;
vector<pair<long, long>> graph[2][100000];

void dijkstra(int src, long dist[], int dir){
	for(int i = 0; i < n; i++) dist[i] = inf;
	dist[src] = 0;
	
	priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
	pq.push(make_pair(0, src));
	
	while(!pq.empty()){
		long c = pq.top().second, d = pq.top().first;
		pq.pop();
		
		if(dist[c] != d) continue;
		
		for(int i = 0; i < graph[dir][c].size(); i++){
			long nc = graph[dir][c][i].first, nd = graph[dir][c][i].second;
			
			if(d + nd < dist[nc]){
				dist[nc] = d + nd;
				pq.push(make_pair(d + nd, nc));
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		long a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		
		graph[0][a].push_back(make_pair(b, c));
		graph[1][b].push_back(make_pair(a, c));
	}
	
	long minv = inf;
	long dist1[n], dist2[n];
	dijkstra(0, dist1, 0);
	dijkstra(n - 1, dist2, 1);
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < graph[0][i].size(); j++){
			minv = min(minv, dist1[i] + dist2[graph[0][i][j].first] + graph[0][i][j].second / 2);
		}
	}
	
	cout << minv << endl;

	return 0;
}