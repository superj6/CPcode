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
int p[maxn], d[maxn];
int val[2][2];
vector<int> g[maxn];
map<vector<int>, int> mp;
int s;
 
int dfs(int c, int p){
	vector<int> v;
	for(int i : g[c]){
		if(i == p) continue;
		v.push_back(dfs(i, c));
	}
	sort(v.begin(), v.end());
	if(mp.find(v) == mp.end()) mp[v] = s++;
	return mp[v];
}

int diam(int c){
	int ret = c;
	for(int i : g[c]){
		if(i == p[c]) continue;
		p[i] = c;
		d[i] = d[c] + 1;
		int cur = diam(i);
		if(d[cur] > d[ret]) ret = cur;
	}
	return ret;
}

int fdiam(int c){
	p[c] = -1, d[c] = 0;
	return diam(c);
}
 
void answer(){
	cin >> n;
	
	s = 0;
	mp.clear();
	for(int t = 0; t < 2; t++){
		for(int i = 0; i < n; i++) g[i].clear();
		for(int i = 0; i < n - 1; i++){
			int u, v;
			cin >> u >> v;
			u--, v--;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		int x = fdiam(fdiam(0));
		for(int i = x; i != -1; i = p[i])
		for(int j = 0; j < 2; j++){
			if(d[i] == d[x] / 2 + j) val[t][j] = dfs(i, -1);
		}
	}
	
	cout << (val[0][0] == val[1][0] || val[0][0] == val[1][1] ? "YES" : "NO") << endl;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();
 
	return 0;
}