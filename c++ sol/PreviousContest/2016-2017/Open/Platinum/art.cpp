#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	freopen("art.in", "r", stdin);
	freopen("art.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int dp[n + 1][n + 1];
	int graph[n][n];
	int color = -1;
	pair<pair<int, int>, pair<int, int>> points[n * n];
	bool works[n * n];

	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < n * n; i++){
		points[i] = make_pair(make_pair(n, n), make_pair(-1, -1));
		works[i] = true;
	} 
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> graph[i][j];
			graph[i][j]--;
			if(graph[i][j] == -1) continue;

			if(color == -1) color = graph[i][j];
			else if(color != graph[i][j]) color = -2;
		
			points[graph[i][j]].first.first = min(points[graph[i][j]].first.first, i);
			points[graph[i][j]].first.second = min(points[graph[i][j]].first.second, j);
			points[graph[i][j]].second.first = max(points[graph[i][j]].second.first, i);
			points[graph[i][j]].second.second = max(points[graph[i][j]].second.second, j);
		}
	}

	if(color != -2){
		cout << n * n - 1 << endl;
		return 0;
	}
	
	for(int i = 0; i < n * n; i++){
		int x = points[i].first.first, y = points[i].first.second, X = points[i].second.first + 1, Y = points[i].second.second + 1;
		if(x == n) continue;
		
		dp[x][y]++;
		dp[x][Y]--;
		dp[X][y]--;
		dp[X][Y]++;
	}
	
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++){
			if(i > 0) dp[i][j] += dp[i - 1][j];
			if(j > 0) dp[i][j] += dp[i][j - 1];
			if(i > 0 && j > 0) dp[i][j] -= dp[i - 1][j - 1];
			
			if(dp[i][j] > 1) works[graph[i][j]] = false;
		}
	}
	
	int cnt = 0;
	for(int i = 0; i < n * n; i++) cnt += works[i];
	
	cout << cnt << endl;

	return 0;
}