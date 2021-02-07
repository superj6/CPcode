#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200, k = 3;
int n, m, p, q;
int a[mxn][mxn], b[mxn][mxn];
int f[mxn], it[mxn];
vector<int> g[mxn], gp[mxn], gq[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		g[--x].push_back(i);
	}
	
	cin >> p >> q;
	
	for(int i = 0; i < p; i++){
		int x, y;
		cin >> x >> y;
		gp[--y].push_back(--x);
	}
	
	for(int i = 0; i < q; i++){
		int x, y;
		cin >> x >> y;
		gq[--x].push_back(--y);
	}
	
	for(int i = 0; i < m; i++){
		for(int j : gq[i]) b[i][j] = 1;
		for(int j : g[i]) b[i][j] = 2;
		for(int j : gp[i]) a[i][j] = 3;
		
		for(int j = 0; j < m; j++) if(i != j)
		for(int l : gq[j]){
			a[i][j] = max(a[i][j], b[i][l]);
		}
	}
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			f[j] = 0, it[j] = j;
			for(int l = 0; l < m; l++){
				f[j] += a[l][i] * b[l][j];
			}
		}
		for(int j : g[i]) f[j] = -1;
		for(int j : gq[i]) f[j] = -1;
		
		partial_sort(it, it + k, it + n, [&](int x, int y){
			return f[x] == f[y] ? x < y : f[x] > f[y];	
		});
		
		for(int j = 0; j < k; j++){
			cout << (it[j] + 1) << (j == k - 1 ? endl : ' ');
		}
	}
	
	return 0;
}