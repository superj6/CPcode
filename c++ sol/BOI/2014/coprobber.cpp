#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

typedef array<int, 3> T;

const int mxn = 500;
int c;
int d[mxn][mxn], f[mxn][mxn];
bool vis[mxn][mxn][2];
queue<T> q;

int start(int n, bool g[mxn][mxn]){
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++)
	for(int k = 0; k < n; k++){
		d[i][j] += g[j][k];
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < 2; j++){
		vis[i][i][j] = 1;
		q.push({i, i, j});
	}
	
	while(!q.empty()){
		T a = q.front();
		q.pop();
		for(int i = 0; i < n; i++){
			if(a[2] && (g[a[0]][i] || i == a[0]) && !vis[i][a[1]][0]){
				vis[i][a[1]][0] = 1;
				q.push({i, a[1], 0});
				f[i][a[1]] = a[0];
			}else if(!a[2] && g[a[1]][i] && !vis[a[0]][i][1] && --d[a[0]][i] <= 0){
				vis[a[0]][i][1] = 1;
				q.push({a[0], i, 1});
			}
		}	
	}
	
	for(int i = 0; i < n; i++) if(!vis[0][i][0]) return -1;
	return 0;
}

int nextMove(int r){
	return c = f[c][r];
}