#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

int n, m, k;
vector<pair<int, int>> graph[50001];

void dijkstra(int dist[], int src){
	for(int i = 0; i <= n; i++) dist[i] = 100000007;
	
	dist[src] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, src));
	
	while(!pq.empty()){
		int cdist = pq.top().first, cur = pq.top().second;
		pq.pop();
		
		if(dist[cur] != cdist) continue;
		
		for(int i = 0; i < graph[cur].size(); i++){
			int next = graph[cur][i].first, ndist = graph[cur][i].second;
			if(cdist + ndist < dist[next]){
				dist[next] = cdist + ndist;
				pq.push(make_pair(cdist + ndist, next));
			}
		}
	}
}

int main(){
	freopen("dining.in", "r", stdin);
	freopen("dining.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k;
	
	for(int i = 0; i < m; i++){
		int a, b, t;
		cin >> a >> b >> t;
		a--, b--;
		
		graph[a].push_back(make_pair(b, t));
		graph[b].push_back(make_pair(a, t));
	}
	
	int dist1[n + 1], dist2[n + 1];
	
	dijkstra(dist1, n - 1);
	
	for(int i = 0; i < k; i++){
		int a, t;
		cin >> a >> t;
		a--;
		
		graph[n].push_back(make_pair(a, dist1[a] - t));
	}
	
	dijkstra(dist2, n);
	
	for(int i = 0; i < n - 1; i++){
		cout << (dist2[i] <= dist1[i]) << endl;
	}

	return 0;
}