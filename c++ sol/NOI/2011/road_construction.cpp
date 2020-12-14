#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, ll>
#define f first
#define s second

const int mxn = 1000000;
int n;
ll sz[mxn];
vector<pi> g[mxn];

ll dfs(int c, int p){
	ll ret = 0;
	sz[c] = 1;
	for(pi i : g[c]){
		if(i.f == p) continue;
		ret += dfs(i.f, c);
		ret += abs(n - 2 * sz[i.f]) * i.s;
		sz[c] += sz[i.f];
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	cout << dfs(0, -1) << endl;

	return 0;
}