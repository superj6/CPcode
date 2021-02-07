//Euler Formula: F + V = E + C + 1
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1002, mxk = mxn * mxn;
int n, m, k, q;
int a[mxn][mxn], f[mxn][mxn], v[mxn][mxn], ex[mxn][mxn], ey[mxn][mxn];
int px[mxk], py[mxk], vis[mxk];

void dfs(int x, int y){
	f[x][y] = k;
	for(int i = 0; i < 2; i++){
		int xx = x + 1 - 2 * i, yy = y + 1 - 2 * i;
		if(ex[x][y - i] && !~f[x][yy]) dfs(x, yy);
		if(ey[x - i][y] && !~f[xx][y]) dfs(xx, y);
	}
}

int ff(int s[mxn][mxn], int x, int y, int X, int Y){
	return x > X || y > Y ? 0 : s[X][Y] - s[x - 1][Y] - s[X][y - 1] + s[x - 1][y - 1];
}

bool wrk(int z, int x, int y, int X, int Y){
	return !vis[z] && px[z] >= x && px[z] <= X && py[z] >= y && py[z] <= Y;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++){
		char c;
		cin >> c;
		a[i][j] = c - 'A' + 1;
	}
	
	for(int i = 1; i <= n + 1; i++)
	for(int j = 1; j <= m + 1; j++){
		f[i][j] = -1;
		ex[i][j] = a[i][j] != a[i - 1][j];
		ey[i][j] = a[i][j] != a[i][j - 1];
	}
	
	for(int i = 1; i <= n + 1; i++)
	for(int j = 1; j <= m + 1; j++){
		if(!~f[i][j]) v[px[k] = i][py[k] = j] = 1, dfs(i, j), k++; 
	}
	
	for(int i = 1; i <= n + 1; i++)
	for(int j = 1; j <= m + 1; j++){
		v[i][j] += v[i - 1][j] + v[i][j - 1] - v[i - 1][j - 1];
		ex[i][j] += ex[i - 1][j] + ex[i][j - 1] - ex[i - 1][j - 1];
		ey[i][j] += ey[i - 1][j] + ey[i][j - 1] - ey[i - 1][j - 1];
	}
	
	while(q--){
		int x, y, X, Y;
		cin >> x >> y >> X >> Y;
		
		int dx = X - x + 1, dy = Y - y + 1;
		int ret = ff(ex, x + 1, y, X, Y) + ff(ey, x, y + 1, X, Y) +
			ff(v, x + 1, y + 1, X, Y) + 2 * (dx + dy) + 1 - (dx + 1) * (dy + 1);
		
		for(int i = x; i <= X + 1; i++){
			if(wrk(f[i][y], x + 1, y + 1, X, Y)) vis[f[i][y]] = 1, ret--;
			if(wrk(f[i][Y + 1], x + 1, y + 1, X, Y)) vis[f[i][Y + 1]] = 1, ret--;
		}
		for(int i = y; i <= Y + 1; i++){
			if(wrk(f[x][i], x + 1, y + 1, X, Y)) vis[f[x][i]] = 1, ret--;
			if(wrk(f[X + 1][i], x + 1, y + 1, X, Y)) vis[f[X + 1][i]] = 1, ret--;
		}
		
		for(int i = x; i <= X + 1; i++) vis[f[i][y]] = vis[f[i][Y + 1]] = 0;
		for(int i = y; i <= Y + 1; i++) vis[f[x][i]] = vis[f[X + 1][i]] = 0;
		
		cout << ret << endl;
	}
	
	return 0;
} 