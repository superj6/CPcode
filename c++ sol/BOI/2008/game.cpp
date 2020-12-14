#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
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
 
const int mxn = 300, k = 4;
pi dd[k] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m;
pi s[2];
int a[mxn][mxn], it[mxn][mxn];
int d[2][mxn][mxn], dp[2][mxn][mxn];
vector<pi> v[2][mxn * mxn];
vector<pi> g[2][mxn][mxn];
queue<pi> q;
 
bool f(pi p){
	return p.f >= 0 && p.s >= 0 && p.f < n && p.s < n && !a[p.f][p.s];
}
 
void answer(){
	cin >> n;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		a[i][j] = c == '#';
		if(isalpha(c)) s[c - 'A'] = {i, j};
		for(int l = 0; l < 2; l++){
			d[l][i][j] = n * n;
			dp[l][i][j] = i == j;
			g[l][i][j].clear();
			v[l][i * n + j].clear();
		}
	}
	
	for(int i = 0; i < 2; i++){
		d[i][s[i].f][s[i].s] = 0;
		q.push(s[i]);
		while(!q.empty()){
			pi c = q.front();
			q.pop();
			int x = d[i][c.f][c.s] + 1;
			for(int j = 0; j < k; j++){
				pi p = c + dd[j];
				int &y = d[i][p.f][p.s];
				if(f(p) && x < y){
					y = x;
					q.push(p);
				}
			}
		}
	}
	
	m = d[0][s[1].f][s[1].s];
	if(m & 1){
		cout << "A" << endl;
		return;
	}
	
	for(pi c = {0, 0}; c.f < n; c.f++)
	for(c.s = 0; c.s < n; c.s++) if(f(c))
	for(int i = 0; i < 2; i++){
		int x = d[i][c.f][c.s];
		if(x + d[!i][c.f][c.s] != m) continue;
		it[c.f][c.s] = v[i][x].size();
		v[i][x].push_back(c);
		for(int j = 0; j < k; j++){
			pi p = c + dd[j];
			if(f(p) && x + 1 + d[!i][p.f][p.s] == m){
				g[i][c.f][c.s].push_back(p);
			}
		}
	}
	
	for(int i = m / 2 - 1, r = i & 1; ~i; i--, r ^= 1)
	for(pi cx : v[0][i])
	for(pi cy : v[1][i]){
		int &dpc = dp[r][it[cx.f][cx.s]][it[cy.f][cy.s]] = 1;
		for(pi px : g[0][cx.f][cx.s]){
			int ret = 0;
			for(pi py : g[1][cy.f][cy.s]){
				ret |= dp[!r][it[px.f][px.s]][it[py.f][py.s]];
			}
			dpc &= ret;
		}
	}
	
	cout << (!dp[0][it[s[0].f][s[0].s]][it[s[1].f][s[1].s]] ? "A" : "B") << endl;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();
 
	return 0;
}