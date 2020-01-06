#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
using namespace std;

int inf = 1000000007;
int n, m, x;
int graph[500][500];
pair<int, pair<int, int>> edges[500];

int dijkstra(){
	int dist[n];
	bool visited[n];
	 
	for(int i = 0; i < n; i++){
		dist[i] = inf;
		visited[i] = false;
	}
	
	dist[0] = 0;
	
	while(true){
		int minindex = -1, mindist = inf;
		
		for(int i = 0; i < n; i++){
			if(!visited[i] && dist[i] < mindist){
				mindist = dist[i];
				minindex = i;
			}
		}
		
		if(minindex == -1 || minindex == n - 1) break;
		visited[minindex] = true;
		
		for(int i = 0; i < n; i++){
			if(graph[minindex][i] != inf) dist[i] = min(dist[i], mindist + graph[minindex][i]);
		}
		
	}
	
	return dist[n - 1];
}

int main(){
	ifstream fin ("mroute.in");
	ofstream fout ("mroute.out");

	fin >> n >> m >> x;
	
	memset(graph, inf, sizeof(graph));
	
	for(int e = 0; e < m; e++){
		int i, j, l, c;
		fin >> i >> j >> l >> c;
		i--, j--;
		
		edges[e].first = c, edges[e].second.first = i, edges[e].second.second = j;
		
		graph[i][j] = l;
		graph[j][i] = l;
	}
	
	sort(edges, edges+m);
	
	int best = inf;

	for(int e = 0; e < m; e++){
		int i = edges[e].second.first, j = edges[e].second.second, c = edges[e].first;
		
		best = min(best, dijkstra() + x / c);
		
		graph[i][j] = inf;
		graph[j][i] = inf;
	}
	
	fout << best << endl;

	return 0;
}