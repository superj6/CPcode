#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n, m;
bool visited[maxn];
unordered_set<int> graph[maxn];
vector<int> ans;

void path(int c){
	while(graph[c].size() > 0){
		int i = *graph[c].begin();
		graph[c].erase(i);
		graph[i].erase(c);
		path(i);
	}
	ans.push_back(c + 1);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		graph[a].insert(b);
		graph[b].insert(a);
	}

	for(int i = 0; i < n; i++){
		if(graph[i].size() % 2){
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}
	
	path(0);
	
	if(ans.size() != m + 1){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	
	cout << ans[0];
	for(int i = 1; i <= m; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}