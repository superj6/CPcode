#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int inf = 1000000007, maxn = 10010;
int n, m;
int dist1[maxn], dist2[maxn], distwrong[maxn];
vector<pair<int, int>> graph1[maxn], graph2[maxn], wrong[maxn];
pair<int, int> roads[maxn];

void dijkstra(vector<pair<int, int>> graph[maxn], int dist[maxn]){
	bool visited[n];
	
	for(int i = 0; i < n; i++){
		visited[i] = false;
		dist[i] = inf;
	}
	
	dist[n - 1] = 0;
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, n - 1));
	
	while(!pq.empty()){
		int cur = pq.top().second;
		int dst = pq.top().first;
		pq.pop();
		
		if(dst != dist[cur]) continue;
		
		for(int i = 0; i < graph[cur].size(); i++){
			int nxt = graph[cur][i].first;
			int c = graph[cur][i].second + dist[cur];
			if(c < dist[nxt]){
				dist[nxt] = c;
				pq.push(make_pair(dist[nxt], nxt));
			}
		}
	}
}

int main(){
	
	ifstream fin ("gpsduel.in");
	ofstream fout ("gpsduel.out");
	
	fin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int x, y;
		fin >> y >> x;
		x--, y--;
		int a, b;
		fin >> a >> b;
		
		graph1[x].push_back(make_pair(y, a)), graph2[x].push_back(make_pair(y, b));
	}
	
	dijkstra(graph1, dist1);
	dijkstra(graph2, dist2);
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < graph1[i].size(); j++){
			int wr = 0;
			
			if(dist1[i] != dist1[graph1[i][j].first] - graph1[i][j].second) wr++;
			if(dist2[i] != dist2[graph1[i][j].first] - graph2[i][j].second) wr++;
			
			wrong[i].push_back(make_pair(graph1[i][j].first, wr));
		}	
	}
	
	dijkstra(wrong, distwrong);
	
	fout << distwrong[0] << endl;

	return 0;
}