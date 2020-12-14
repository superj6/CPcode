#include "fun.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int mxn = 500;
int vis[mxn];
int g[mxn][mxn];
vi ans;

/*
int hoursRequired(int x, int y){
	return g[x][y];
}
*/

vi createFunTour(int n, int q){
	int x = 0, y = 0;
	for(int i = 0; i < n; i++)
	for(int j = 0; j < i; j++){
		g[i][j] = g[j][i] = hoursRequired(i, j);
		if(g[i][j] > y) x = i, y = g[i][j];
	}
	
	for(int i = 0; i < n; i++){
		vis[x] = 1;
		ans.push_back(y = x);
		for(int j = 0; j < n; j++){
			if(!vis[j] && g[y][j] > g[y][x]) x = j;
		}
	}
	
	return ans;
}

/*
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	memset(g, 0x3f, sizeof(g));
	for(int i = 0; i < n; i++) g[i][i] = 0;
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		g[u][v] = g[v][u] = 1;
	}
	
	for(int k = 0; k < n; k++)
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	}
	
	vi v = createFunTour(n, q);
	
	for(int i : v) cout << i << " ";
	cout << endl;

	return 0;
}
*/