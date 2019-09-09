#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

int n;
int graph[500][500];
bool visited[500][500];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool inbound(int x, int y){
	if(x < 0 || y < 0 || x >= n || y >= n) return false;
	return true;
}

int recur(int x, int y, int diff){
	visited[x][y] = true;
	int sum = 1;
	
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i], ny = y + dy[i];
		if(inbound(nx, ny)) if(!visited[nx][ny] && abs(graph[x][y] - graph[nx][ny]) <= diff) sum += recur(nx, ny, diff);
	}
	
	return sum;
}

bool works(int diff){
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) visited[i][j] = false;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(!visited[i][j]) if(recur(i, j, diff) >= ceil(pow(n, 2) / 2)){
				return true;
			}
		}
	}
	
	return false;
}

int binary(int minv, int maxv){
	if(minv == maxv) return minv;
	int middle = (minv + maxv) / 2;
	
	bool works0 = works(middle), works1 = works(middle + 1);
	
	if(works1 && !works0) return middle + 1;
	if(works0) return binary(minv, middle);
	return binary(middle + 1, maxv);
}

int main(){
	ifstream fin ("tractor.in");
	ofstream fout ("tractor.out");

	fin >> n;
	
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) fin >> graph[i][j];
	
	fout << binary(0, 1000000) << endl;

	return 0;
}