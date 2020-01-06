#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const int maxk = 200, maxn = 20000, inf = 1000000007;
int n, m, k, q;
int hubs[maxn];
int *dist[maxk];
vector<pair<int, int>> graph[maxn];

int* dijkstra(int src){
	int* dist = new int[n];
	
	for(int i = 0; i < n; i++){
		dist[i] = inf;
	}
	
	dist[src] = 0;
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, src));
	
	while(!pq.empty()){
		int mindist = pq.top().first, minindex = pq.top().second;
		pq.pop();
		
		if(dist[minindex] != mindist) continue;
		
		for(int i = 0; i < graph[minindex].size(); i++){
			int next = graph[minindex][i].first, ndist = graph[minindex][i].second;
			
			if((hubs[minindex] >= 0 || hubs[next] >= 0) && mindist + ndist < dist[next]){
				dist[next] = mindist + ndist;
				pq.push(make_pair(dist[next], next));
			} 
		}
	}
	
	return dist;
}

int bestdist(int a, int b){
	if(hubs[a] >= 0) return dist[hubs[a]][b];
	
	int minv = inf;
	
	for(int i = 0; i < graph[a].size(); i++){
		int next = graph[a][i].first, ndist = graph[a][i].second;
			
		if(hubs[next] >= 0) if(dist[hubs[next]][b] != inf) minv = min(minv, dist[hubs[next]][b] + ndist);
	}
	
	return minv;
}

int main(){
	freopen("vacationgold.in", "r", stdin);
	freopen("vacationgold.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k >> q;
	
	for(int i = 0; i < m; i++){
		int u, v, d;
		cin >> u >> v >> d;
		u--, v--;
		
		graph[u].push_back(make_pair(v, d));
	}
	
	for(int i = 0; i < n; i++) hubs[i] = -1;
	
	for(int i = 0; i < k; i++){
		int id;
		cin >> id;
		id--;
		
		hubs[id] = i;
	}
	
	for(int i = 0; i < n; i++){
		if(hubs[i] != -1){
			dist[hubs[i]] = dijkstra(i);
		} 
	}
	
	int amt = 0, total = 0;
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		int cdist = bestdist(a, b);
		
		if(cdist != inf){
			amt++;
			total += cdist;
		}
	}
	
	cout << amt << endl << total << endl;

	return 0;
}