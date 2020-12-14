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

const int mxn = 100000;
int n;
int id[mxn], rid[mxn], sz[mxn];
vector<int> g[mxn];
int ans[mxn];
int t;

int dfs(int c, int p){
	sz[c] = 1, rid[id[c] = t++] = c;
	for(int i : g[c]) if(i != p) sz[c] += dfs(i, c);
	return sz[c];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	dfs(0, -1);
	
	ll ret = 0;
	for(int i = 0; i < n; i++){
		ret += 2 * min(sz[i], n - sz[i]);
		ans[rid[(id[i] + n / 2) % n]] = i + 1;
	} 
	
	cout << ret << endl;
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}