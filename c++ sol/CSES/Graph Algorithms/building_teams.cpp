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
	
	int team[n];
	vector<int> graph[n];
	
	memset(team, -1, sizeof(team));
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	queue<int> q;
	
	for(int i = 0; i < n; i++){
		if(team[i] != -1) continue;
		
		q.push(i);
		team[i] = 0;
		
		while(!q.empty()){
			int c = q.front();
			q.pop();
			
			for(int i = 0; i < (int)graph[c].size(); i++){\
				if(team[graph[c][i]] == -1){
					team[graph[c][i]] = !team[c];
					q.push(graph[c][i]);
				}else if(team[c] == team[graph[c][i]]){
					cout << "IMPOSSIBLE" << endl;
					return 0;
				}
			}
		}
	}
	
	cout << team[0] + 1;
	for(int i = 1; i < n; i++) cout << " " << team[i] + 1;
	cout << endl;

	return 0;
}