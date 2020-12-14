#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000, mxm = 200000;
int n, m;
int u[mxm], v[mxm], vis[mxm], p[mxm];
bool a[mxn][mxn];
vector<int> g[mxn], gr[mxm];

void dfs(int c){
	vis[c] = 1;
	for(int i : gr[c]){
		if(!vis[i]){
			p[i] = c;
			dfs(i);
		}else if(i != p[c] && !~-vis[i]){
			cout << (i < m ? u[i] : v[i]) + 1;
			for(int j = c; j != i; j = p[j]){
				cout << " " << (j < m ? u[j] : v[j]) + 1;
			}
			cout << endl;
			exit(0);
		}
	}
	vis[c] = 2;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i];
		u[m + i] = --u[i], v[m + i] = --v[i];
		a[u[i]][v[i]] = a[v[i]][u[i]] = 1;
		g[u[i]].push_back(i);
		g[v[i]].push_back(i);
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < g[i].size(); j++)
	for(int l = 0; l < j; l++){
		int x = g[i][j], y = g[i][l];
		if(!a[i ^ u[x] ^ v[x]][i ^ u[y] ^ v[y]]){
			gr[(i == u[x]) * m + x].push_back((i == v[y]) * m + y);
			gr[(i == u[y]) * m + y].push_back((i == v[x]) * m + x);
		} 
	}
	
	for(int i = 0; i < m; i++) if(!vis[i]) p[i] = -1, dfs(i);
	
	cout << "no" << endl;

	return 0;
}