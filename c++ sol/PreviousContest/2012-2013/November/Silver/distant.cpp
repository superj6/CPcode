#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

int inf = 1000000007;
int n, a, b;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
char graph[40][40];

bool inrange(int x, int y){
	if(x < 0 || x >= n || y < 0 || y >= n) return false;
	return true;
}

int dijmax(int src){
	int srx = src % n, sry = src / n;
	int dist[n][n];
	bool visited[n][n];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			dist[i][j] = inf;
			visited[i][j] = inf;
		}
	}
	
	dist[srx][sry] = 0;
	
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	
	pq.push(make_pair(0, src));
	
	while(!pq.empty()){
		int dst = pq.top().first, cur = pq.top().second;
		int x = cur % n, y = cur / n;
		pq.pop();
		
		if(dist[x][y] != dst) continue;
		
		for(int i = 0; i < 4; i++){
			int nx = x + dx[i], ny = y + dy[i];
			if(!inrange(nx, ny)) continue;
			int ndst = dst + (graph[x][y] == graph[nx][ny] ? a : b);
			
			if(ndst < dist[nx][ny]){
				dist[nx][ny] = ndst;
				pq.push(make_pair(ndst, nx + n * ny));
			}
		}
	}
	
	int maxd = 0;
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) maxd = max(maxd, dist[i][j]);
	
	return maxd;
}

int main(){
	ifstream fin ("distant.in");
	ofstream fout ("distant.out");
	
	fin >> n >> a >> b;
	
	for(int i = 0; i < n; i++){
		fin >> graph[i];
	}
	
	int maxv = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			maxv = max(maxv, dijmax(i + j * n));
		}
	}
	
	fout << maxv << endl;

	return 0;
}