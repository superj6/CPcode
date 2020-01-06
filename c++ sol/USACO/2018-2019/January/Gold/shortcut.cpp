/*
	First run dijkstras from node 1. As you do dijkstras store a previous array, and make the previous value be the minimum
node index possible such that it has the shortest path. Then create a tree adding an edge from each node to its previous array.
Lastly, dfs the tree from node 1 and for each node store the amount of cows within its subtree, and find the node such that
its subtree cows sum * (distance - t) is maximum, as this is for each node the change in distance by all the cows going through
there by adding a new path. The complexity of this is O(nlogn) from dijkstras.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const int inf = 1000000007, maxn = 10000;
int n, m, t;
int dist[maxn], cows[maxn], amt[maxn];
vector<int> nextv[maxn];
vector<pair<int, int>> graph[maxn];

void dijkstra(){
	int prev[n];
	
	for(int i = 0; i < n; i++){
		prev[i] = -1;
		dist[i] = inf;
	}
	
	dist[0] = 0;
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, 0));
	
	while(!pq.empty()){
		int cdist = pq.top().first, cur = pq.top().second;
		pq.pop();
		
		if(dist[cur] != cdist) continue;
		
		if(prev[cur] != -1){
			nextv[prev[cur]].push_back(cur);
		}
		
		for(int i = 0; i < graph[cur].size(); i++){
			int next = graph[cur][i].first, ndist = graph[cur][i].second;
			
			if(cdist + ndist < dist[next]){
				dist[next] = cdist + ndist;
				prev[next] = cur;
				pq.push(make_pair(cdist + ndist, next));
			}else if(cdist + ndist == dist[next] && cur < prev[next]){
				prev[next] = cur;
			}
			
		}
	}
}

void dfs(int cur){
	amt[cur] = cows[cur];
	
	for(int i = 0; i < nextv[cur].size(); i++){
		dfs(nextv[cur][i]);
		amt[cur] += amt[nextv[cur][i]];
	}
}

int main(){
	freopen("shortcut.in", "r", stdin);
	freopen("shortcut.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> t;
	
	for(int i = 0; i < n; i++) cin >> cows[i];
	
	for(int i = 0; i < m; i++){
		int a, b, t; 
		cin >> a >> b >> t;
		a--, b--;
		
		graph[a].push_back(make_pair(b, t));
		graph[b].push_back(make_pair(a, t));
	}
	
	dijkstra();
	
	dfs(0);
	
	long maxv = 0;

	for(int i = 0; i < n; i++){
		maxv = max(maxv, (long)amt[i] * (dist[i] - t));
	}
	
	cout << maxv << endl;

	return 0;
}
