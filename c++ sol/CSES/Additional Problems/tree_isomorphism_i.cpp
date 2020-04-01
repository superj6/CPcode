#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
vector<int> g[2][maxn];
map<vector<int>, int> mp;
int s;

int dfs(int t, int c, int p){
	vector<int> v;
	for(int i : g[t][c]){
		if(i == p) continue;
		v.push_back(dfs(t, i, c));
	}
	sort(v.begin(), v.end());
	if(mp.find(v) == mp.end()) mp[v] = s++;
	return mp[v];
}

void answer(){
	cin >> n;
	
	s = 0;
	mp.clear();
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < n; i++) g[t][i].clear();
		for(int i = 0; i < n - 1; i++){
			int u, v;
			cin >> u >> v;
			u--, v--;
			g[t][u].push_back(v);
			g[t][v].push_back(u);
		}
	}
	
	cout << (dfs(0, 0, -1) == dfs(1, 0, -1) ? "YES" : "NO") << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}