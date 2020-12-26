#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000, w = 4;
const int dx[w] = {1, 0, -1, 0};
const int dy[w] = {0, 1, 0, -1};
int n, k;
int a[mxn][mxn], d[mxn][mxn], dd[mxn][mxn], dp[mxn][mxn], ff[mxn][mxn], vis[mxn][mxn];
queue<pi> q;

int f(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < n;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	memset(d, 0x3f, sizeof(d));
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		a[i][j] = c == 'S' ? -1 : c == '#';
		if(!~-a[i][j]) d[i][j] = 0, q.push({i, j});
	}
	
	while(!q.empty()){
		int cx = q.front().f, cy = q.front().s;
		q.pop();
		for(int i = 0; i < w; i++){
			int x = cx + dx[i], y = cy + dy[i];
			if(f(x, y) && d[x][y] > d[cx][cy] + 1){
				d[x][y] = d[cx][cy] + 1;
				q.push({x, y});
			}
		}
	}
	
	memset(dd, 0x3f, sizeof(dd));
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		if(!~a[i][j]) dd[i][j] = 0, q.push({i, j});
	}
	
	while(!q.empty()){
		int cx = q.front().f, cy = q.front().s;
		q.pop();
		dp[cx][cy] = dd[cx][cy] / k + 1; 
		for(int i = 0; i < w; i++){
			int x = cx + dx[i], y = cy + dy[i];
			if(f(x, y)){
				if(dd[cx][cy] % k == k - 1 && d[x][y] == dd[cx][cy] / k + 1){
					dp[x][y] = dd[cx][cy] / k + 1;
				}else if(dd[x][y] > dd[cx][cy] + 1 && d[x][y] > (dd[cx][cy] + 1) / k){
					dd[x][y] = dd[cx][cy] + 1;
					q.push({x, y});
				}
			}
		}
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		if(dp[i][j]) ff[i][j] = dp[i][j], q.push({i, j});
	}
	
	int ret = 0;
	while(!q.empty()){
		int cx = q.front().f, cy = q.front().s;
		q.pop();
		ret += !vis[cx][cy];
		vis[cx][cy] = 1;
		if(ff[cx][cy] > 1) for(int i = 0; i < w; i++){
			int x = cx + dx[i], y = cy + dy[i];
			if(f(x, y) && ff[x][y] < ff[cx][cy] - 1){
				ff[x][y] = ff[cx][cy] - 1;
				q.push({x, y});
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}