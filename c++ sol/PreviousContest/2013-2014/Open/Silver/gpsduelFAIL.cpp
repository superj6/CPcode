#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int inf = 1000000007;
int n, m;
int dist1[1000], dist2[1000], distwrong[1000];
int graph1[1000][1000], graph2[1000][1000], wrong[1000][1000];
pair<int, int> roads[5000];

void dijkstra(int graph[1000][1000], int dist[1000]){
	bool visited[n];
	
	for(int i = 0; i < n; i++){
		visited[i] = false;
		dist[i] = inf;
	}
	
	dist[n - 1] = 0;
	
	while(true){
		int minindex = -1, mindist = inf;
		
		for(int i = 0; i < n; i++){
			if(!visited[i] && dist[i] < mindist){
				mindist = dist[i];
				minindex = i;
			}
		}
		
		if(minindex == -1) break;
		visited[minindex] = true;
		
		for(int i = 0; i < n; i++){
			if(graph[i][minindex] != inf) dist[i] = min(dist[i], mindist + graph[i][minindex]);
		}
	}
}

int main(){
	
	ifstream fin ("gpsduel.in");
	ofstream fout ("gpsduel.out");
	
	fin >> n >> m;
	
	for(int i = 0; i < n; i++) for(int j = i; j < n; j++){
		graph1[i][j] = inf, graph1[j][i] = inf;
		graph2[i][j] = inf, graph2[j][i] = inf;
		wrong[i][j] = inf, wrong[j][i] = inf;
	}
	
	for(int i = 0; i < m; i++){
		fin >> roads[i].first >> roads[i].second;
		roads[i].first--, roads[i].second--;
		fin >> graph1[roads[i].first][roads[i].second] >> graph2[roads[i].first][roads[i].second];
		wrong[roads[i].first][roads[i].second] = 0;
	}
	
	dijkstra(graph1, dist1);
	dijkstra(graph2, dist2);
	
	for(int i = 0; i < m; i++){
		if(dist1[roads[i].first] != dist1[roads[i].second] + graph1[roads[i].first][roads[i].second]) wrong[roads[i].first][roads[i].second]++;
		if(dist2[roads[i].first] != dist2[roads[i].second] + graph2[roads[i].first][roads[i].second]) wrong[roads[i].first][roads[i].second]++;
	}
	
	dijkstra(wrong, distwrong);
	
	fout << distwrong[0] << endl;

	return 0;
}