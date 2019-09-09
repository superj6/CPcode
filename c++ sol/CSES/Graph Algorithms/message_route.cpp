#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	int par[n];
	vector<int> graph[n];
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	queue<int> q;
	q.push(0);
	memset(par, -1, sizeof(par));
	
	while(!q.empty()){
		int c = q.front();
		q.pop();
		
		if(c == n - 1){
			vector<int> path;
			
			while(c != -1){
				path.push_back(c + 1);
				c = par[c];
			}
			
			reverse(path.begin(), path.end());
			cout << path.size() << endl;
			
			cout << path[0];
			for(int i = 1; i < path.size(); i++) cout << " " << path[i];
			cout << endl;
			
			return 0;
		}
		
		for(int i = 0; i < graph[c].size(); i++){
			if(par[graph[c][i]] != -1 || par[c] == graph[c][i]) continue;
			par[graph[c][i]] = c;
			q.push(graph[c][i]);
		}
	}
	
	cout << "IMPOSSIBLE" << endl;

	return 0;
}