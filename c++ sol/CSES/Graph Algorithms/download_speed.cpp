#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 500;
int n, m;
long graph[maxn][maxn];

long maxflow(){
	long total = 0;
	long maxflow, maxloc;
	long flow[maxn], par[maxn];
	bool visited[maxn];
	
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
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		graph[a][b] += c;
	}
	
	cout << maxflow() << endl;

	return 0;
}