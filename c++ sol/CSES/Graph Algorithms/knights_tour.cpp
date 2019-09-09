#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
 
int ans[8][8];
int dx[8] = {2, 2, 1, -1, -2, -2, -1, 1};
int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
 
bool works(int x, int y){
	if(x < 0 || x >= 8 || y < 0 || y >= 8) return 0;
	if(ans[x][y]) return 0;
	return 1;
}
 
bool dfs(int x, int y, int cnt){
	ans[x][y] = cnt;
	if(cnt == 64) return 1;
	int bc = 9;
	
	for(int i = 0; i < 8; i++){
		int nx = x + dx[i], ny = y + dy[i], nc = 0;
		if(!works(nx, ny)) continue;
		
		for(int j = 0; j < 8; j++){
			if(works(nx + dx[j], ny + dy[j])) nc++;
		}
		
		bc = min(bc, nc);
	}
	
	for(int i = 0; i < 8; i++){
		int nx = x + dx[i], ny = y + dy[i], nc = 0;
		if(!works(nx, ny)) continue;
		
		for(int j = 0; j < 8; j++){
			if(works(nx + dx[j], ny + dy[j])) nc++;
		}
		
		if(nc == bc && dfs(nx, ny, cnt + 1)) return 1;
	}
	
	ans[x][y] = 0;
	return 0;
}
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int x, y;
	cin >> x >> y;
	x--, y--;
	
	dfs(y, x, 1);
	
	for(int i = 0; i < 8; i++){
		cout << ans[i][0];
		for(int j = 1; j < 8; j++) cout << " " << ans[i][j];
		cout << endl;
	}
	
	return 0;
}