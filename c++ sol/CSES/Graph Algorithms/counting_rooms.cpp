#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 1000;
int n, m;
int r = 0;
char grid[maxn][maxn];
int room[maxn][maxn];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool works(int x, int y){
	if(x < 0 || y < 0 || x >= n || y >= m) return false;
	if(grid[x][y] == '#') return false;
	if(room[x][y] != -1) return false;
	return true;
}

void flood(int x, int y){
	room[x][y] = r;
	for(int i = 0; i < 4; i++) if(works(x + dx[i], y + dy[i])) flood(x + dx[i], y + dy[i]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	memset(room, -1, sizeof(room));
	for(int i = 0; i < n; i++) cin >> grid[i];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(grid[i][j] == '.' && room[i][j] == -1){
				flood(i, j);
				r++;
			}
		}
	}
	
	cout << r << endl;

	return 0;
}