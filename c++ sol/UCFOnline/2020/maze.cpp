#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

const int mxn = 100, w = 4;
const pi d[w] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m;
pi k;
char a[mxn][mxn];
int vis[mxn][mxn];
queue<pi> q;

bool wrk(pi p){
	return p.f >= 0 && p.s >= 0 && p.f < n && p.s < m && ~vis[p.f][p.s];
}

void answer(){
	cin >> n >> m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		cin >> a[i][j];
		if(a[i][j] == '*'){
			k = {i, j};
			a[i][j] = '9';
		}
		vis[i][j] = 10 * (a[i][j] == 'F');
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++) if(a[i][j] == 'G'){
		vis[i][j] = -1;
		for(int l = 0; l < w; l++){
			pi p = (pi){i, j} + d[l];
			if(wrk(p)) vis[p.f][p.s] = -1;
		}
	}
	
	while(!q.empty()) q.pop();
	for(int i = 0; i < n; i++){
		if(!vis[i][0] && a[i][0] == '1') vis[i][0] = 1, q.push({i, 0});
		if(!vis[i][m - 1] && a[i][m - 1] == '1') vis[i][m - 1] = 1, q.push({i, m - 1});
	}
	for(int i = 0; i < m; i++){
		if(!vis[0][i] && a[0][i] == '1') vis[0][i] = 1, q.push({0, i});
		if(!vis[n - 1][i] && a[n - 1][i] == '1') vis[n - 1][i] = 1, q.push({n - 1, i});
	}
	
	while(!q.empty()){
		pi c = q.front();
		q.pop();
		for(int l = 0; l < w; l++){
			pi p = c + d[l];
			if(!wrk(p)) continue;
			if(a[c.f][c.s] == 'E'){
				if(!vis[p.f][p.s]) vis[p.f][p.s] = 1, q.push(p);
			}else if(a[c.f][c.s] == 'F'){
				if(!vis[p.f][p.s] && a[p.f][p.s] > '0' + vis[c.f][c.s]) vis[p.f][p.s] = 1, q.push(p);
			}else if(a[c.f][c.s] == 'P'){
				if(!vis[p.f][p.s] && a[p.f][p.s] < '0' + vis[c.f][c.s]) vis[p.f][p.s] = 1, q.push(p);
			}else{
				if(a[p.f][p.s] == 'E'){
					if(!vis[p.f][p.s]) vis[p.f][p.s] = 1, q.push(p);
				}else if(a[p.f][p.s] == 'F'){
					if(a[c.f][c.s] < '0' + vis[p.f][p.s]) vis[p.f][p.s] = a[c.f][c.s] - '0', q.push(p);
				}else if(a[p.f][p.s] == 'P'){
					if(a[c.f][c.s] > '0' + vis[p.f][p.s]) vis[p.f][p.s] = a[c.f][c.s] - '0', q.push(p);
				}else{
					if(!vis[p.f][p.s] && abs(a[c.f][c.s] - a[p.f][p.s]) <= 1) vis[p.f][p.s] = 1, q.push(p);
				}
			}
		}
	}
	
	cout << (vis[k.f][k.s] ? "You've got this!" : "Find another way") << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}