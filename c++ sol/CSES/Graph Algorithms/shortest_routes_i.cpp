#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'

const int maxn = 100000;
const long inf = 100000000000007;
int n, m;
long dist[maxn];
vector<pair<long, long>> graph[maxn];

void dijkstra(){
	for(int i = 0; i < n; i++) dist[i] = inf;
	
	priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
	pq.push(make_pair(0, 0));
	dist[0] = 0;
	
	while(!pq.empty()){
		long c = pq.top().second, d = pq.top().first;
		pq.pop();
		
		if(dist[c] != d) continue;
		
		for(int i = 0; i < graph[c].size(); i++){
			int nc = graph[c][i].first, nd = graph[c][i].second;
			
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
		
		graph[a].push_back(make_pair(b, c));
	}
	
	dijkstra();
	
	cout << dist[0];
	for(int i = 1; i < n; i++) cout << " " << dist[i];
	cout << endl;

	return 0;
}