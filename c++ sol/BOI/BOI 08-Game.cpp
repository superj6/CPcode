/*
  Realize that only paths of shortest distance between A and B matter, since if a player travels off path one step it will take one
step to get back on, and jumping a player only subtracts one step needed to take, so it is never optimal to get off path. This means we
only have to think of states where A and B are the same distance from their starting point. If the distance between A and B is odd,
B will never be able to jump A while on the shortest path, and since A moves first, A will always win. However, if the distance is even
B can win only if no matter what A's move is, B can always reach a superset of the shortest path midpoints that A can reach after that
move. After crossing the midpoint the winner is determined, so you only have to think about the positions A and B can be at before
the midpoint. This leads us to do dp based on pairs of A and B positions where the distance A and B are from their starting positions
is the same. Let dp[dist][A pos][B pos] be 1 if B can win when A and B are currently at those positions, and 0 otherwise. We try moving
A forward all directions it can go where it is still on a shortest path, and for each of those positions B must be able to jump to a 
winning state dp[dist + 1][A jump pos][B jump pos]. Obviously the base case is for midpoint distances, the dp is 1 only for when the points
are equal, and 0 otherwise. You then just print out whoever wins at dp[0][A start][B start]. To not use too much memory, only hold the 
current and next highest distance in the dp array.
*/

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
