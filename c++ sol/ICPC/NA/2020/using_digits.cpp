#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define int ll
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

const int mxn = 200, k = 4;
const int dx[k] = {1, 0, -1, 0};
const int dy[k] = {0, 1, 0, -1};
int n, m;
string s;
int a[mxn][mxn];
int dp[mxn][mxn][mxn];
priority_queue<pii, vector<pii>, greater<pii>> pq;

bool f(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> m >> n >> s;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		char c;
		cin >> c;
		a[i][j] = c - '0';
	}
	
	int ret = 0x3f3f3f3f3f3f3f3f;
	memset(dp, 0x3f, sizeof(dp));
	dp[0][n - 1][0] = a[n - 1][0];
	for(int t = 0; t <= s.size(); t++){
		if(t){
			for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++){
				//dp[t][i][j] = dp[t - 1][i][j];
				for(int l = 0; l < k; l++){
					int z = s[t - 1] - '0' + 1;
					int x = i + z * dx[l], y = j + z * dy[l];
					if(f(x, y)){
						dp[t][i][j] = min(dp[t][i][j], a[i][j] + dp[t - 1][x][y]);
					}
				}
			}
		}
		for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++){
			pq.push({dp[t][i][j], {i, j}});
		}
		while(!pq.empty()){
			int d = pq.top().f, x = pq.top().s.f, y = pq.top().s.s;
			pq.pop();
			if(dp[t][x][y] != d) continue;
			for(int i = 0; i < k; i++){
				int xx = x + dx[i], yy = y + dy[i];
				if(f(xx, yy) && dp[t][xx][yy] > a[xx][yy] + d){
					pq.push({dp[t][xx][yy] = a[xx][yy] + d, {xx, yy}});
				}
			}
		}
		ret = min(ret, dp[t][0][m - 1]);
	}
	
	cout << ret << endl;
	
	return 0;
}