#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const long inf = 50000000000007;
int n, m;
vector<pair<int, pair<int, long>>> edges;

void bf(){
	long dist[n];
	int prev[n];
	for(int i = 0; i < n; i++) dist[i] = inf;
	dist[0] = 0;
	
	for(int i = 0; i < n - 1; i++){
		bool any = 0;
		for(int j = 0; j < edges.size(); j++){
			long u = edges[j].first, v = edges[j].second.first, w = edges[j].second.second;
			
			if(dist[u] + w < dist[v]){
				dist[v] = dist[u] + w;
				prev[v] = u;
				any = 1;
			}
		}
		if(!any) break;
	}
	
	for(int j = 0; j < edges.size(); j++){
		long u = edges[j].first, v = edges[j].second.first, w = edges[j].second.second;
		
		if(dist[u] + w < dist[v]){
			cout << "YES" << endl;
			
			for(int i = 0; i < n; i++) v = prev[v];
			
			vector<int> path(1, v + 1);
			for(int i = prev[v]; i != v; i = prev[i]) path.push_back(i + 1);
			
			reverse(path.begin(), path.end());
			
			cout << v + 1;
			for(int i = 0; i < path.size(); i++) cout << " " << path[i];
			cout << endl;
			
			return;
		}
	}
	
	cout << "NO" << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		long a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		edges.push_back(make_pair(a, make_pair(b, c)));
	}
	
	bf();
	
	return 0;
}