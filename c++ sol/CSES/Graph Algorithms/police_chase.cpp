#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define endl '\n'

const int maxn = 500;
int n, m;
int graph[maxn][maxn];
pair<int, int> edge[2 * maxn];
bool visited[maxn];

long maxflow(){
	int total = 0;
	int maxflow, maxloc;
	int flow[maxn], par[maxn];
	int visited[maxn];

	while(true){
		memset(flow, 0, sizeof(flow));
		memset(par, -1, sizeof(par));
		memset(visited, 0, sizeof(visited));
		flow[0] = 1000000007;
		
		while(true){
			maxflow = 0, maxloc = -1;
			for(int i = 0; i < n; i++){
				if(!visited[i] && flow[i] > maxflow){
					maxflow = flow[i];
					maxloc = i;
				}
			}
			
			if(maxloc == -1 || maxloc == n - 1) break;
			visited[maxloc] = 1;
			
			for(int i = 0; i < n; i++){
				if(flow[i] < min(maxflow, graph[maxloc][i])){
					flow[i] = min(maxflow, graph[maxloc][i]);
					par[i] = maxloc;
				}
			}
		}
		
		if(maxloc == -1) break;
		total += maxflow;
		
		int cur = n - 1;
		while(cur != 0){
			int nx = par[cur];
			graph[nx][cur] -= maxflow;
			graph[cur][nx] += maxflow;
			cur = nx;
		}
	}
	
	return total;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		edge[i] = {a, b};
		graph[a][b]++;
		graph[b][a]++;
	}
	
	cout << maxflow() << endl;
	
	queue<int> q;
	q.push(0);
	visited[0] = 1;
	
	while(!q.empty()){
		int c = q.front();
		q.pop();
		
		for(int i = 0; i < n; i++){
			if(!visited[i] && graph[c][i] > 0){
				q.push(i);
				visited[i] = 1;
			}
		}
	}
	
	for(int i = 0; i < m; i++){
		int a = edge[i].first, b = edge[i].second;
		if(visited[a] ^ visited[b]) cout << a + 1 << " " << b + 1 << endl;
	}

	return 0;
}