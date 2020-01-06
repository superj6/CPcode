#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <set>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<int, pi>

const int inf = 0x3f3f3f3f;
const int maxn = 15, maxm = 50;
int n, r, c;
int grid[maxm][maxm];
int graph[maxn][maxn];
int dp[1 << maxn][maxn];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool works(int x, int y){
	if(x < 0 || x >= r || y < 0 || y >= c) return 0;
	return 1;
}

void flood(int x, int y){
	grid[x][y] = n;
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(works(nx, ny) && grid[nx][ny] == -1) flood(nx, ny);
	}
}

void dijk(int sx, int sy){
	int dist[r][c];
	memset(dist, inf, sizeof(dist));
	dist[sx][sy] = 0;
	
	set<pii> pq;
	pq.insert({0, {sx, sy}});
	
	while(!pq.empty()){
		int d = (*pq.begin()).first, x = (*pq.begin()).second.first, y = (*pq.begin()).second.second;
		pq.erase(pq.begin());
		
		if(grid[x][y] >= 0) graph[n][grid[x][y]] = min(graph[n][grid[x][y]], d);
		
		for(int i = 0; i < 4; i++){
			int nx = x + dx[i], ny = y + dy[i];
			if(works(nx, ny)){
				int nd = d + (grid[nx][ny] >= 0 ? 0 : grid[nx][ny] == -2 ? 1 : inf);
				if(nd < dist[nx][ny]){
					pq.erase({dist[nx][ny], {nx, ny}});
					dist[nx][ny] = nd;
					pq.insert({nd, {nx, ny}});
				}
			}
		}
	}
}

int main() {
	freopen("island.in", "r", stdin);
	freopen("island.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> r >> c;
	
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			char l;
			cin >> l;
			if(l == 'X') grid[i][j] = -1;
			if(l == 'S') grid[i][j] = -2;
			if(l == '.') grid[i][j] = -3;
		}
	} 
	
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(grid[i][j] == -1){
				flood(i, j);
				n++;
			}
		}
	}
	
	n = 0;
	memset(graph, inf, sizeof(graph));
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(grid[i][j] == n){
				dijk(i, j);
				n++;
			}
		}
	}
	
	int ret = inf;
	memset(dp, inf, sizeof(dp));
	for(int i = 1; i < (1 << n); i++){
		for(int j = 0; j < n; j++){
			if(i & (1 << j)){
				if(__builtin_popcount(i) == 1) dp[i][j] = 0;
				for(int l = 0; l < n; l++){
					if(~i & (1 << l)){
						dp[i | (1 << l)][l] = min(dp[i | (1 << l)][l], dp[i][j] + graph[j][l]);
					}
				}
			}
			if(i == (1 << n) - 1) ret = min(ret, dp[i][j]);
		}
	}
	
	cout << ret << endl;
	
	return 0;
}