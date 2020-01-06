#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n, m;
vector<pi> graph[maxn];
int used[maxn];
bool rip;

void dfs(int c, int d){
	used[c] = d + 1;
	for(pi i : graph[c]){
		if(used[i.first]) rip |= (used[c] - 1 != (used[i.first] - 1) ^ i.second);
		else dfs(i.first, d ^ i.second);
	}
}

int main(){
	freopen("revegetate.in", "r", stdin);
	freopen("revegetate.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		char c;
		int x, y;
		cin >> c >> x >> y;
		x--, y--;
		
		graph[x].push_back({y, (c == 'S' ? 0 : 1)});
		graph[y].push_back({x, (c == 'S' ? 0 : 1)});
	}
	
	int ret = 0;
	for(int i = 0; i < n; i++){
		if(!used[i]){
			dfs(i, 0);
			ret++;
		}
	}
	
	if(rip) cout << 0 << endl;
	else cout << ("1" + string(ret, '0')) << endl;

	return 0;
}