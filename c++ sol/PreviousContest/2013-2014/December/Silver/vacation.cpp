#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int n, m, k, q;
long inf = 1000000007;
long graph[200][200];
long distkf[100][200], distkb[100][200];

void dijkstra(long dist[200], int source){
	bool visited[n];
	
	for(int i = 0; i < n; i++){
		dist[i] = inf;
		visited[i] = false;
	}
	
	dist[source] = 0;
	
	while(true){
		int minindex = -1;
		long mindist = inf;
		
		for(int i = 0; i < n; i++){
			if(!visited[i] && dist[i] < mindist){
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
}

int main(){
	ifstream fin ("vacation.in");
	ofstream fout ("vacation.out");

	fin >> n >> m >> k >> q;	
	
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) graph[i][j] = inf;
	
	for(int i = 0; i < m; i++){
		int u, v;
		long d;
		fin >> u >> v >> d;
		u--, v--;
		graph[u][v] = min(graph[u][v], d);
	}
	
	
	for(int i = 0; i < k; i++) dijkstra(distkf[i], i);
	
	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			int temp = graph[i][j];
			graph[i][j] = graph[j][i];
			graph[j][i] = temp;
		}
	}
	
	for(int i = 0; i < k; i++) dijkstra(distkb[i], i);
	
	int valid = 0;
	long total = 0;

	
	for(int i = 0; i < q; i++){
		int a, b;
		fin >> a >> b;
		a--, b--;
		
		long mindist = inf;
		
		for(int j = 0; j < k; j++){
			mindist = min(mindist, distkb[j][a] + distkf[j][b]);
		}
		
		if(mindist != inf){
			valid++;
			total += mindist;
		}
		
	}
	
	fout << valid << endl << total << endl;

	return 0;
}