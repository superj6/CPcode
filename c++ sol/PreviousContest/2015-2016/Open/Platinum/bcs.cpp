#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <unordered_map>
#include <vector>
using namespace std;
#define endl '\n'

const int n = 100;
long hm = 1000000007;
long ha[n][n];

void genpows(){
	ha[0][0] = 100000007;
	
	for(int j = 1; j < n; j++) ha[0][j] = (ha[0][j - 1] * ha[0][0]) % hm;
	
	for(int i = 1; i < n; i++) ha[i][n - 1] = (ha[i - 1][n - 1] * ha[0][n - 1]) % hm;
}

struct shape{
	int r, c;
	int fx = -1, fy = -1;
	char piece[n][n];
	long hashv[n][n];
	
	long hext(long h, int ch, int p){
		return (h * ha[0][p] + ch) % hm;
	}

	int num(char ch){
		return (ch == '.' ? 0 : ch - 'a' + 1);
	}
	
	bool ischar(int x, int y){
		return piece[x][y] != '.';
	}
	
	int charat(int x, int y){
		return piece[x][y];
	}
	
	shape(char grid[n][n], int r, int c){
		this->r = r;
		this->c = c;
		memcpy(piece, grid, sizeof(piece));
		
		for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++){
			hashv[i][j] = hext((j == 0 ? 0 : hashv[i][j - 1]), num(grid[i][j]), 0);
			if(fx == -1 && ischar(i, j)) fx = i, fy = j;
		}
		
		for(int j = 0; j < c; j++)
		for(int i = 1; i < r; i++){
			hashv[i][j] = hext(hashv[i - 1][j], hashv[i][j], n - 1);
		}
	}
	
	long gethash(int x = 0, int y = 0, int X = -1, int Y = -1){
		if(X == -1) X = r - 1, Y = c - 1;
		int a = X - x, b = Y - y;
		long out = hashv[X][Y];
		if(x > 0) out -= (ha[n - 1][a] * hashv[x - 1][Y]) % hm;
		if(out < 0) out += hm;
		if(y > 0) out -= (ha[0][b] * hashv[X][y - 1]) % hm;
		if(out < 0) out += hm;
		if(x > 0 && y > 0) out += (((ha[n - 1][a] * ha[0][b]) % hm) * hashv[x - 1][y - 1]) % hm;
		out %= hm;
		
		return out;
	}
};

int k, r, c;
int fx, fy;
char grid[n][n];
bool used[n][n][n];
shape *bull;
shape *part[n][2][4];
unordered_map<long, vector<int>> parth;

void fliph(){
	char ngrid[n][n];
	
	for(int i = 0; i < r; i++)
	for(int j = 0; j < c; j++){
		ngrid[i][j] = grid[i][c - j - 1];
	}
	
	memcpy(grid, ngrid, sizeof(ngrid));
}

void flipv(){
	char ngrid[n][n];
	
	for(int i = 0; i < r; i++)
	for(int j = 0; j < c; j++){
		ngrid[i][j] = grid[r - i - 1][j];
	}
	
	memcpy(grid, ngrid, sizeof(ngrid));
}

void rotate(){
	char ngrid[n][n];
	
	for(int i = 0; i < r; i++)
	for(int j = 0; j < c; j++){
		ngrid[j][i] = grid[r - i - 1][j];
	}
	
	memcpy(grid, ngrid, sizeof(ngrid));
}

bool issame(shape *p){
	if(fx - p->fx < 0 || p->r - p->fx > r - fx) return false;
	if(fy - p->fy < 0 || p->c - p->fy > c - fy) return false;
	
	for(int i = 0; i < p->r; i++)
	for(int j = 0; j < p->c; j++){
		if(p->ischar(i, j) && p->charat(i, j) != grid[i + fx - p->fx][j + fy - p->fy]) return false;
	}
	
	return true;
}

bool fitpiece(shape *p[4]){
	for(int z = 0; z < 4; z++){
		if(!issame(p[z])) continue;
		
		for(int i = 0; i < p[z]->r; i++)
		for(int j = 0; j < p[z]->c; j++){
			if(p[z]->ischar(i, j)) grid[i + fx - p[z]->fx][j + fy - p[z]->fy] = '.';
		}
		
		for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++){
			if(grid[i][j] != '.'){
				fx = i;
				fy = j;
				return true;
			}
		}
		
		return false;
	}
	
	return false;
}

int main(){
	//freopen("bcs.in", "r", stdin);
	//freopen("bcs.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	memset(used, 0, sizeof(used));
	genpows();
	
	cin >> k >> r >> c;
	for(int i = 0; i < r; i++) cin >> grid[i];
	
	bull = new shape(grid, r, c);
	
	for(int i = 0; i < k; i++){
		cin >> r >> c;
		for(int j = 0; j < r; j++) cin >> grid[j];
		
		for(int j = 0; j < 2; j++){
			for(int l = 0; l < 4; l++){
				part[i][j][l] = new shape(grid, r, c);
				parth[part[i][j][l]->gethash()].push_back(i);
				
				if(l % 2 == 0) fliph();
				else flipv();
			}
			rotate();
			swap(r, c);
		}
		
	}
	
	r = bull->r, c = bull->c;
	int total = 0;
	
	for(int a = 0; a < k; a++)
	for(int b = 0; b < k; b++){
		if(a == b) continue;
		
		for(int s = 0; s < 2; s++)
		for(int t = 0; t < 2; t++){
			shape *part1[4], *part2[4];
			for(int i = 0; i < 4; i++) part1[i] = part[a][s][i], part2[i] = part[b][t][i];
			
			memcpy(grid, bull->piece, sizeof(bull->piece));
			
			fx = bull->fx, fy = bull->fy;
			
			if(!fitpiece(part1)) continue;
			if(!fitpiece(part2)) continue;
			
			shape *last = new shape(grid, r, c);
			
			int lx = 100, ly = 100, rx = -1, ry = -1;
			for(int i = 0; i < r; i++)
			for(int j = 0; j < c; j++){
				if(last->ischar(i, j)){
					lx = min(lx, i);
					ly = min(ly, j);
					rx = max(rx, i);
					ry = max(ry, j);
				}
			}
			
			vector<int> sol = parth[last->gethash(lx, ly, rx, ry)];
			
			delete last;
			
			for(int i = 0; i < sol.size(); i++){
				if(!used[a][b][sol[i]] && sol[i] != a && sol[i] != b){
					total++;
					used[a][b][sol[i]] = used[a][sol[i]][b] = used[b][a][sol[i]] = used[b][sol[i]][a] = used[sol[i]][a][b] = used[sol[i]][b][a] = true;
				}
			}
		}
	}
	
	cout << total << endl;

	return 0;
}