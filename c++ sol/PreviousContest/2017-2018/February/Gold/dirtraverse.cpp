#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n;
long file[maxn], sz[maxn];
vector<int> graph[maxn];
long ans;

long dfs1(int c){
	if(!graph[c].size()){
		file[c] = 1;
		return sz[c];
	}
	
	long ret = 0;
	for(int i : graph[c]){
		ret += dfs1(i);
		file[c] += file[i];
		
	}
	
	return ret + file[c] * (sz[c] + 1);
}

void dfs2(int c, long ret){
	ans = min(ans, ret);
	
	for(int i : graph[c]){
		if(!graph[i].size()) continue;
		dfs2(i, ret - file[i] * (sz[i] + 1) + 3 * (file[0] - file[i]));
	}
}

int main(){
	freopen("dirtraverse.in", "r", stdin);
	freopen("dirtraverse.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int m;
		string s;
		cin >> s >> m;
		
		sz[i] = s.size();
		graph[i].resize(m);
		
		for(int j = 0; j < m; j++){
			cin >> graph[i][j];
			graph[i][j]--;
		}
	}
	
	ans = dfs1(0) - file[0] * (sz[0] + 1);
	dfs2(0, ans);
	
	cout << ans << endl;

	return 0;
}