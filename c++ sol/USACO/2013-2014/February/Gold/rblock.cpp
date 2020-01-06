#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int inf = 100000007;
int n, m;
int graph[250][250];
int dist[250], prevv[250];
bool visited[250];

void dijkstra(bool prevSet){
	for(int i = 0; i < n; i++){
		dist[i] = inf;
		if(prevSet) prevv[i] = -1;
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
		
		if(minindex == -1) break;
		visited[minindex] = true;
		
		for(int i = 0; i < n; i++){
			if(mindist + graph[minindex][i] < dist[i]){
				dist[i] = mindist + graph[minindex][i];
				if(prevSet) prevv[i] = minindex;
			}
		}
		
	}
	
}

int main(){
	freopen("rblock.in", "r", stdin);
	freopen("rblock.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;
	
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) graph[i][j] = inf;
	
	for(int i = 0; i < m; i++){
		int a, b, l;
		cin >> a >> b >> l;
		a--, b--;
		
		graph[a][b] = l;
		graph[b][a] = l;
	}
	
	dijkstra(true);
	
	int path = n - 1, mindist = dist[n - 1], maxdist = 0;
	
	while(path != 0){
		graph[path][prevv[path]] *= 2;
		graph[prevv[path]][path] *= 2;
		
		dijkstra(false);
		maxdist = max(maxdist, dist[n - 1]);
		
		graph[path][prevv[path]] /= 2;
		graph[prevv[path]][path] /= 2;
		
		path = prevv[path];
	}
	
	cout << (maxdist - mindist) << endl;
	
	return 0;
}