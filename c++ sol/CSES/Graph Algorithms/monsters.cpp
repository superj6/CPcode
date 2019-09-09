#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define endl '\n'

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
char d[4] = {'D', 'R', 'U', 'L'};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	queue<pair<int, int>> q;
	pair<int, int> a;
	
	int vis[n][m], vis2[n][m], par[n][m];
	char grid[n][m];
	for(int i = 0; i < n; i++){
		cin >> grid[i];
		
		for(int j = 0; j < m; j++){
			par[i][j] = -1;
			vis[i][j] = vis2[i][j] = 1000000007;
			
			if(grid[i][j] == 'A'){
				a = make_pair(i, j);
				vis2[i][j] = 0;
			}else if(grid[i][j] == 'M'){
				vis[i][j] = 0;
				q.push(make_pair(i, j));
			}else if(grid[i][j] == '#'){
				vis[i][j] = vis2[i][j] = -1;
			}
			
		}
	}
	
	while(!q.empty()){
		int x = q.front().first, y = q.front().second;
		q.pop();
		
		for(int i = 0; i < 4; i++){
			int nx = x + dx[i], ny = y + dy[i];
			
			if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
			if(vis[nx][ny] <= vis[x][y] + 1) continue;
			
			vis[nx][ny] = vis[x][y] + 1;
			q.push(make_pair(nx, ny));
		}
	}
	
	q.push(a);
	
	while(!q.empty()){
		int x = q.front().first, y = q.front().second;
		q.pop();
		
		if(x == 0 || y == 0 || x == n - 1 || y == m - 1){
			vector<char> path;
			
			while(par[x][y] != -1){
				path.push_back(d[(par[x][y] + 2) % 4]);
				int nx = x + dx[par[x][y]];
				int ny = y + dy[par[x][y]];
				x = nx, y = ny;
			}
			
			reverse(path.begin(), path.end());
			int k = (int)path.size();
			
			cout << "YES" << endl;
			cout << k << endl;
			for(int i = 0; i < k; i++) cout << path[i];
			cout << endl;
			
			return 0;
		}
		
		for(int i = 0; i < 4; i++){
			int nx = x + dx[i], ny = y + dy[i];
			
			if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
			if(vis[nx][ny] <= vis2[x][y] + 1 || vis2[nx][ny] <= vis2[x][y] + 1) continue;
			
			vis2[nx][ny] = vis2[x][y] + 1;
			par[nx][ny] = (i + 2) % 4;
			q.push(make_pair(nx, ny));
		}
	}
	
	cout << "NO" << endl;

	return 0;
}