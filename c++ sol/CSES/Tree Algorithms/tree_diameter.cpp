#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n;
vector<int> graph[maxn];

pair<int, int> dfs(int c, int p){
	pair<int, int> ret = {c, 0};
	for(int i : graph[c]){
		if(i == p) continue;
		pair<int, int> cur = dfs(i, c);
		if(cur.second >= ret.second){
			ret = cur;
			ret.second++;
		}
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	int r = dfs(0, -1).first;
	
	cout << dfs(r, -1).second << endl;

	return 0;
}