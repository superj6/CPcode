#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<pi, pi>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

const int mxn = 200000, m = 301;
int n, w = m, h = m, W, H;
pi s;
pi x[mxn], y[mxn];
int vis[mxn];
int a[m][m], v[m][m];
vector<int> g[m][m];
queue<int> q;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> x[i].f >> x[i].s >> y[i].f >> y[i].s;
	
	cin >> s.f >> s.s;
	
	for(int i = 0; i < n; i++){
		g[x[i].f][x[i].s].push_back(i);
		g[y[i].f][y[i].s].push_back(i);
		if(x[i].f == y[i].f){
			if(x[i].s > y[i].s) swap(x[i], y[i]);
			if(x[i].f == s.f && x[i].s <= s.s && s.s <= y[i].s){
				q.push(i);
			}
		}else{
			if(x[i].f > y[i].f) swap(x[i], y[i]);
			if(x[i].s == s.s && x[i].f <= s.f && s.f <= y[i].f){
				q.push(i);
			}
		}
	}
	
	while(!q.empty()){
		int c = q.front();
		q.pop();
		vis[c] = 1;
		w = min({w, x[c].f, y[c].f});
		h = min({h, x[c].s, y[c].s});
		W = max({W, x[c].f, y[c].f});
		H = max({H, x[c].s, y[c].s});
		if(!v[x[c].f][x[c].s]){
			v[x[c].f][x[c].s] = 1;
			for(int i : g[x[c].f][x[c].s]){
				if(!vis[i]) q.push(i);
			}
		}
		if(!v[y[c].f][y[c].s]){
			v[y[c].f][y[c].s] = 1;
			for(int i : g[y[c].f][y[c].s]){
				if(!vis[i]) q.push(i);
			}
		}
		for(pi i = x[c], d = {y[c].f > x[c].f, y[c].s > x[c].s}; i != y[c]; i = i + d){
			a[i.f][i.s] = 1;
		}
		a[y[c].f][y[c].s] = 1;
	}
	
	for(int j = H; j >= h; j--){
		for(int i = w; i <= W; i++) cout << (a[i][j] ? '#' : '.');
		cout << endl;
	}

	return 0;
}