#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int inf = 1000000007;
int n, m;
int graph[250][250];

int dist(){
	int dist[250];
	bool visited[250];
	
	for(int i = 0; i < n; i++){
		dist[i] = inf;
		visited[i] = false;
	}
	
	dist[0] = 0;
	
	while(true){
		int minindex = -1, mindist = inf;
		
		for(int i = 0; i < n; i++){
			if(dist[i] < mindist && !visited[i]){
				mindist = dist[i];
				minindex = i;
			}
		}
		
		if(minindex == -1) break;
		
		visited[minindex] = true;
		
		for(int i = 0; i < n; i++){
			dist[i] = min(dist[i], mindist + graph[minindex][i]);
		}
	}
	
	return dist[n - 1];
}

int main(){
	ifstream fin ("rblock.in");
	ofstream fout ("rblock.out");
	
	fin >> n >> m;
	
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) graph[i][j] = inf;
	
	for(int i = 0; i < m; i++){
		int a, b, l;
		fin >> a >> b >> l;
		a--, b--;
		
		graph[a][b] = l;
		graph[b][a] = l;
	}
	
	int length = dist(), maxv = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(graph[i][j] != inf){
				graph[i][j] *= 2;
				graph[j][i] *= 2;
				
				maxv = max(maxv, dist() - length);
				
				graph[i][j] /= 2;
				graph[j][i] /= 2;
			}
		}
	}
	
	fout << maxv << endl;

	return 0;
}