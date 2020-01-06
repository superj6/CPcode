#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100;
int t, n, m;
char grid[maxn][maxn];
int dist[maxn][maxn];
int dir[maxn];
queue<pi> q;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool works(int x, int y){
  if(x < 0 || x >= n || y < 0 || y >= m) return 0;
  return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

  memset(dir, -1, sizeof(dir));
  dir['U'] = 0;
  dir['L'] = 1;
  dir['D'] = 2;
  dir['R'] = 3;
	
  cin >> t >> n >> m;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> grid[i][j];
      if(grid[i][j] == 'S'){
        q.push({i, j});
        dist[i][j] = 0;
      }else{
        dist[i][j] = t + 1;
      }
    }
  }

  while(!q.empty()){
    int x = q.front().first, y = q.front().second;
    q.pop();
    
    if(x == 0 || x == n - 1 || y == 0 || y == m - 1){
      cout << dist[x][y] << endl;
      return 0;
    }

    for(int i = 0; i < 4; i++){
      int nx = x + dx[i], ny = y + dy[i];
      if(!works(nx, ny) || dist[x][y] + 1 >= dist[nx][ny]) continue;

      if(grid[nx][ny] == '0' || dir[grid[nx][ny]] == i){
        dist[nx][ny] = dist[x][y] + 1;
        q.push({nx, ny});
      }
    }
  }

  cout << "NOT POSSIBLE" << endl; 

	return 0;
}