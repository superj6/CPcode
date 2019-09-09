#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int m, n, amount = 0, startx, starty;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int graph[500][500], locs[500][500];
bool test[500][500];

bool inbound(int x, int y){
	if(x < 0 || y < 0 || x >= m || y >= n) return false;
	if(test[x][y]) return false;
	return true;
}

int recurse(int x, int y, int dif){
	test[x][y] = true;
	
	int out = 0;
	
	if(locs[x][y]) out++;
	
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		
		if(inbound(nx, ny)) if(abs(graph[x][y] - graph[nx][ny]) <= dif) out += recurse(nx, ny, dif);
	}
	
	return out;

}

bool works(int dif){
	
	for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) test[i][j] = false;

	if(recurse(startx, starty, dif) == amount) return true;
	return false;
}

int binary(int minv, int maxv){
	if(minv == maxv) return minv;
	
	int mid = (minv + maxv) / 2;
	
	bool works0 = works(mid), works1 = works(mid + 1);
	
	if(!works0 && works1) return mid + 1;
	if(!works1) return binary(mid + 1, maxv);
	return binary(minv, mid);
}

int main(){
	ifstream fin ("ccski.in");
	ofstream fout ("ccski.out");

	fin >> m >> n;
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			fin >> graph[i][j];	
		}
	}
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			fin >> locs[i][j];
			if(locs[i][j]){
				amount++;
				startx = i, starty = j;
			}
		}
	}
	
	fout << binary(0, 1000000000) << endl;

	return 0;
}