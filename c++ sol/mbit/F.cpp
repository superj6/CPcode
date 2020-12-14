#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

const int mxn = 1002, w = 4;
const pi d[w] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const char f[w] = {'S', 'E', 'N', 'W'};
int n, m, k, q;
string s;
int a[mxn][mxn];
vector<pi> g[w], v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k >> q;
	
	cin >> s;
	
	for(int i = 0; i < k; i++){
		int x, y;
		cin >> x >> y;
		a[x][y] = 1;
	}
	
	for(int i = 1; i <= n; i++) a[i][0] = a[i][m + 1] = 1;
	for(int i = 1; i <= m; i++) a[0][i] = a[n + 1][i] = 1;
	
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++) if(a[i][j])
	for(int l = 0; l < w; l++){
		pi p = (pi){i, j} + d[l];
		if(!a[p.f][p.s]) g[l].push_back(p);
	}
	
	for(char c : s){
		int x = find(f, f + w, c) - f;
		swap(g[x], v);
		g[x].clear();
		for(pi i : v) if(!a[i.f][i.s]){
			k++, a[i.f][i.s] = 1;
			for(int j = 0; j < w; j++){
				pi p = i + d[j];
				if(!a[p.f][p.s]) g[j].push_back(p);
			}
		}
		cout << k << endl;
	}

	return 0;
}