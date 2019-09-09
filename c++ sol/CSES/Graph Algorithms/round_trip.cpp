#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int par[maxn], rnk[maxn];

int find(int x){
	return par[x] == x ? x : find(par[x]);
}

void unionf(int x, int y){
	if(rnk[x] < rnk[y]) swap(x, y);
	else if(rnk[x] == rnk[y]) rnk[x]++;
	
	par[y] = x;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	vector<int> graph[n];
	
	for(int i = 0; i < n; i++){
		par[i] = i;
		rnk[i] = 0;
	}
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		int x = find(a), y = find(b);
		
		if(x != y){
			unionf(x, y);
			graph[a].push_back(b);
			graph[b].push_back(a);
			continue;
		}
		
		queue<int> q;
		q.push(a);
		memset(par, -1, sizeof(par));
		
		while(q.front() != b){
			int c = q.front();
			q.pop();
			
			for(int j = 0; j < (int)graph[c].size(); j++){
				if(graph[c][j] == par[c]) continue;
				
				par[graph[c][j]] = c;
				q.push(graph[c][j]);
			}
		}
		
		vector<int> path;
		
		while(b != -1){
			path.push_back(b);
			b = par[b];
		}
		
		int k = (int)path.size();

		cout << k + 1 << endl;
		cout << path[k - 1] + 1;
		for(int i = 0; i < k; i++) cout << " " << path[i] + 1;
		cout << endl;
		
		return 0;
	}
	
	cout << "IMPOSSIBLE" << endl;

	return 0;
}