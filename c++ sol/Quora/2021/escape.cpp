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

const int mxn = 1000, w = 4;
const pi dd[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, m, k;
pi s, e;
int a[mxn][mxn], d[mxn][mxn], dp[mxn][mxn];
vector<pi> v[mxn * mxn + 1];
queue<pi> q;

bool f(pi x){
	return x.f >= 0 && x.f < n && x.s >= 0 && x.s < m && !a[x.f][x.s];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		char c;
		cin >> c;
		a[i][j] = c == '#';
		if(c == 'S') s = {i, j};
		else dp[i][j] = n * m;
		if(c == 'E') e = {i, j};
		d[i][j] = -1;
	}
	
	for(int i = 0; i < k; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		cin >> d[x][y];
		v[d[x][y]].push_back({x, y});
	}
	
	for(int i = n * m; ~i; i--)
	for(pi c : v[i]){
		if(d[c.f][c.s] != i) continue;
		for(int j = 0; j < w; j++){
			pi p = c + dd[j];
			if(f(p) && d[p.f][p.s] < i - 1){
				d[p.f][p.s] = i - 1;
				v[i - 1].push_back(p);
			}
		}
	}
	
	if(!~d[s.f][s.s]) q.push(s);
	while(!q.empty()){
		pi c = q.front();
		q.pop();
		if(c == e){
			cout << dp[c.f][c.s] << endl;
			return 0;
		}
		for(int i = 0; i < w; i++){
			pi p = c + dd[i];
			if(f(p) && !~d[p.f][p.s] && dp[p.f][p.s] > dp[c.f][c.s] + 1){
				dp[p.f][p.s] = dp[c.f][c.s] + 1;
				q.push(p);
			}
		}
	}
	
	cout << "IMPOSSIBLE" << endl;
	
	return 0;
}