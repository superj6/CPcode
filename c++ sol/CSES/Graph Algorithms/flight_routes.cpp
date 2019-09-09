#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 100000;
const long inf = 100000000000007;
int n, m, k;
long dist[maxn];
long prv[maxn];
vector<pair<long, long>> graph[2][maxn];

void dijkstra(){
	for(int i = 0; i < n; i++){
		dist[i] = inf;
		prv[i] = -1;
	}
	dist[n - 1] = 0;
	
	priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
	pq.push(make_pair(0, n - 1));
	
	while(!pq.empty()){
		long c = pq.top().second, d = pq.top().first;
		pq.pop();
		
		if(dist[c] != d) continue;
		
		for(auto e : graph[1][c]){
			long nc = e.first, nd = e.second;
			
			if(d + nd <= dist[nc]){
				dist[nc] = d + nd;
				prv[nc] = c;
				pq.push(make_pair(d + nd, nc));
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < m; i++){
		long a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		graph[0][a].push_back(make_pair(b, c));
		graph[1][b].push_back(make_pair(a, c));
	}
	
	dijkstra();
	
	priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
	pq.push(make_pair(dist[0], 0));
	
	for(int i = 0; i < k - 1; i++){
		long c = pq.top().second, d = pq.top().first;
		pq.pop();
		
		cout << d << " ";
		d -= dist[c];
		
		for(; c != -1; c = prv[c]){
			long a = -1;
			for(auto e : graph[0][c]){
				long nc = e.first, nd = e.second;
				if(nc == prv[c] && dist[nc] + nd == dist[c] && a == -1){
					a = nd;
					continue;
				}
 				
				pq.push(make_pair(d + nd + dist[nc], nc));
			}
			d += a;
		}
	}
	
	cout << pq.top().first << endl;
	
	return 0;
}