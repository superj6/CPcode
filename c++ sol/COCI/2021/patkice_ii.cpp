#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 2000, mxk = mxn * mxn, w = 4;
const char dc[w + 3] = {'v', '>', '^', '<', 'o', 'x', '.'};
const int dx[w] = {1, 0, -1, 0};
const int dy[w] = {0, 1, 0, -1};
int n, m, k, s, t;
int a[mxn][mxn];
int d[mxk], p[mxk], vis[mxk];
vector<pi> g[mxk];
deque<int> q;

int id(int x, int y){ return x * m + y;}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	k = n * m;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		char c;
		cin >> c;
		a[i][j] = find(dc, dc + w + 3, c) - dc;
		
		if(a[i][j] == w) s = id(i, j);
		else d[id(i, j)] = k;
		if(a[i][j] == w + 1) t = id(i, j);
		
		for(int l = 0; l < w; l++){
			int x = i + dx[l], y = j + dy[l];
			if(x >= 0 && x < n && y >= 0 && y < m){
				g[id(i, j)].push_back({id(x, y), a[i][j] != l && a[i][j] != w});
			}
		}
	}
	 
	q.push_front(s);
	while(!q.empty()){
		int c = q.front();
		q.pop_front();
		if(vis[c]) continue;
		vis[c] = 1;
		for(pi i : g[c]){
			if(d[i.f] > d[c] + i.s){
				d[i.f] = d[c] + i.s, p[i.f] = c;
				if(i.s) q.push_back(i.f);
				else q.push_front(i.f);
			}
		}
	}
	
	for(int i = t; i != s; i = p[i]){
		if(d[i] != d[p[i]]){
			int x = i / m, y = i % m, px = p[i] / m, py = p[i] % m;
			a[px][py] = (x < px || y < py) << 1 | (y != py);
		}
	}
	
	cout << d[t] << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++) cout << dc[a[i][j]];
		cout << endl;
	}
	
	return 0;
}