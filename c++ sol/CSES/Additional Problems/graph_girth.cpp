#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 2500;
int n, m;
vector<int> graph[maxn];

int bfs(int x){
	int dist[n], prv[n];
	memset(dist, -1, sizeof(dist));
	memset(prv, -1, sizeof(prv));
	
	queue<int> q;
	q.push(x);
	dist[x] = 0;
	
	int ret = n + 1;
	while(!q.empty()){
		int c = q.front();
		q.pop();
		
		for(int i : graph[c]){
			if(dist[i] == -1){
				dist[i] = dist[c] + 1;
				prv[i] = c;
				q.push(i);
			}else if(i != prv[c]){
				ret = min(ret, dist[i] + dist[c] + 1);
			}
		}
	}
	
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	int ret = n + 1;
	for(int i = 0; i < n; i++){
		ret = min(ret, bfs(i));
	}
	
	cout << (ret == n + 1 ? -1 : ret) << endl;

	return 0;
}