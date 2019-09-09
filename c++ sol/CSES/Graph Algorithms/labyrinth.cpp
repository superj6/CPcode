#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string.h>
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
	
	char grid[n][m];
	int prev[n][m];
	pair<int, int> a, b;
	
	memset(prev, -1, sizeof(prev));
	
	for(int i = 0; i < n; i++){
		cin >> grid[i];
		for(int j = 0; j < m; j++){
			if(grid[i][j] == 'A'){
				a = make_pair(i, j);
			}
			if(grid[i][j] == 'B'){
				b = make_pair(i, j);
			}
		}
	}
	
	queue<pair<int, int>> q;
	q.push(a);
	prev[a.first][a.second] = 4;
	
	while(!q.empty()){
		pair<int, int> cur = q.front();
		q.pop();
		
		if(cur == b){
			cout << "YES" << endl;
			vector<char> move;
			
			int x = cur.first, y = cur.second;
			
			while(prev[x][y] != 4){
				move.push_back(d[(prev[x][y] + 2) % 4]);
				int nx = x + dx[prev[x][y]];
				int ny = y + dy[prev[x][y]];
				x = nx;
				y = ny;
			}
			
			reverse(move.begin(), move.end());
			cout << move.size() << endl;
			
			for(int i = 0; i < move.size(); i++) cout << move[i];
			cout << endl;
			
			return 0;
		}
		
		for(int i = 0; i < 4; i++){
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			
			if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
			if(grid[nx][ny] == '#') continue;
			if(prev[nx][ny] != -1) continue;
			
			prev[nx][ny] = (i + 2) % 4;
			q.push(make_pair(nx, ny));
		}
	}
	
	cout << "NO" << endl;

	return 0;
}