#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int a, b, n;
const long long inf = 9223372036854700, mod = 1000;
long long graph[mod][mod];

long long dijkstra(){
	bool visited[mod];
	long long dist[mod];
	
	for(int i = 0; i < mod; i++){
		visited[i] = false;
		dist[i] = inf;
	}
	
	dist[a] = 0;
	
	while(true){
		long long mindist = inf;
		int minindex = -1;
		
		for(int i = 0; i < mod; i++){
			if(!visited[i] && dist[i] != inf && dist[i] < mindist){
				mindist = dist[i];
				minindex = i;
			}
		}
		
		if(minindex == -1) return -1 * mod - 1;
		if(minindex == b) return dist[b];
		
		visited[minindex] = true;
		
		for(int i = 0; i < mod; i++){
			if(graph[minindex][i] != inf && i != minindex) dist[i] = min(dist[i], mindist + graph[minindex][i]);
		}
	}
	
	return 696969696;
}

int main(){
	ifstream fin ("cowroute.in");
	ofstream fout ("cowroute.out");

	fin >> a >> b >> n;
	a--, b--;
	
	for(int i = 0; i < mod; i++){
		
		for(int j = 0; j < mod; j++) graph[i][j] = inf;
		graph[i][i] = 0;
	} 
	
	for(int i = 0; i < n; i++){
		int m;
		long long cost;
		fin >> cost >> m;
		cost *= mod;
		
		int temp[m];
		
		for(int j = 0; j < m; j++){
			fin >> temp[j];
			temp[j]--;
			
			for(int k = 0; k < j; k++){
				
				//graph[temp[j]][temp[k]] = min(graph[temp[j]][temp[k]], cost + j - k);
				graph[temp[k]][temp[j]] = min(graph[temp[k]][temp[j]], cost + j - k);
			}
		}
	}
	
	long long answer = dijkstra();
	
	fout << (answer / mod) << " " << (answer % mod) << endl;

	return 0;
}