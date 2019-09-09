#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define endl '\n'
 
const int maxn = 100000, mod = 1000000007;
const long inf = 100000000000007;
int n, m;
bool works[maxn];
long cnt[maxn], amt[maxn][3];
long dist[maxn];
queue<int> q;
vector<pair<long, long>> graph[2][maxn];
 
void dijkstra(){
	for(int i = 0; i < n; i++){
		amt[i][0] = amt[i][2] = -1;
		amt[i][1] = inf;
		dist[i] = inf;
	}
	dist[n - 1] = 0;
	
	priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;
	pq.push(make_pair(0, n - 1));
	
	while(!pq.empty()){
		long c = pq.top().second, d = pq.top().first;
		pq.pop();
		
		if(dist[c] != d) continue;
		
		for(pair<long, long> e : graph[1][c]){
			long nc = e.first, nd = e.second;
			
			if(d + nd < dist[nc]){
				dist[nc] = d + nd;
				pq.push(make_pair(d + nd, nc));
			}
		}
	}
}

void dfs(int c){
	amt[c][0] = 0;
	for(pair<long, long> i : graph[0][c]){
		long nc = i.first, nd = i.second;
		if(dist[nc] + nd == dist[c]){
			cnt[nc]++;
			if(amt[nc][0] == -1) dfs(nc);
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
	
	dijkstra();
	dfs(0);
	
	amt[0][0] = 1;
	amt[0][1] = amt[0][2] = 0;
	q.push(0);
	
	while(!q.empty()){
		int c = q.front();
		q.pop();
		
		for(pair<long, long> i : graph[0][c]){
			long nc = i.first, nd = i.second;
			
			if(dist[nc] + nd == dist[c]){
				cnt[nc]--;
				amt[nc][0] += amt[c][0];
				amt[nc][0] %= mod;
				amt[nc][1] = min(amt[nc][1], amt[c][1] + 1);
				amt[nc][2] = max(amt[nc][2], amt[c][2] + 1);
				if(cnt[nc] == 0) q.push(nc);
			}
			
		}
	}
	
	cout << dist[0] << " " << amt[n - 1][0] << " " << amt[n - 1][1] << " " << amt[n - 1][2] << endl;
	
	return 0;
}	