#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
#define endl '\n'

const int sz = 500;
int m, n, t;

int rankf[sz * sz], parent[sz * sz], best[sz * sz];
int grid[sz][sz];

int find(int x){
	int px = parent[x];
	if(parent[px] != px) find(px);
	
	if(best[x] == -1) best[x] = (best[px] == -1 ? best[parent[px]] : best[px]);
	
	parent[x] = parent[px];
	return parent[x];
	
}

void unionf(int val, int x, int y){
	x = find(x);
	y = find(y);
	
	if(x == y) return;
	
	if(rankf[x] + rankf[y] >= t){
		if(rankf[x] < t) best[x] = val;
		if(rankf[y] < t) best[y] = val;
	}
	
	parent[y] = x;
	rankf[x] += rankf[y];
}

int main(){
	freopen("skilevel.in", "r", stdin);
	freopen("skilevel.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> m >> n >> t;
	
	vector<pair<int, pair<int, int>>> edges;
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			int cur = i * n + j;
			rankf[cur] = 1;
			parent[cur] = cur;
			best[cur] = -1;
			
			cin >> grid[i][j];
			
			if(i > 0) edges.push_back(make_pair(abs(grid[i][j] - grid[i - 1][j]), make_pair(cur - n, cur)));
			if(j > 0) edges.push_back(make_pair(abs(grid[i][j] - grid[i][j - 1]), make_pair(cur - 1, cur)));
		}
	}
	
	sort(edges.begin(), edges.end());
	
	for(int i = 0; i < edges.size(); i++){
		unionf(edges[i].first, edges[i].second.first, edges[i].second.second);
	}
	
	long long sum = 0;
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			int test;
			cin >> test;
			if(test){
				find(i * n + j);
				sum += best[i * n + j];
			} 
		}
	}
	
	cout << sum << endl;
	
	return 0;
}