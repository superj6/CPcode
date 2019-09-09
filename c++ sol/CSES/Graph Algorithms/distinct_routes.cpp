#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 500;
int n, m;
int graph[maxn][maxn];
int g[maxn][maxn];
vector<int> ans;

long maxflow(){
	int total = 0;
	int maxflow, maxloc;
	int flow[maxn], par[maxn];
	int visited[maxn];
	int graph[maxn][maxn];
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) graph[i][j] = ::graph[i][j];

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
			if(::graph[nx][cur]) g[nx][cur]++;
			else g[cur][nx]--;
			cur = nx;
		}
	}
	
	return total;
}

void dfs(int c){
	ans.push_back(c + 1);
	for(int i = 0; i < n; i++){
		if(g[c][i]){
			g[c][i]--;
			dfs(i);
			return;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		graph[a][b]++;
	}
	
	int mflow = maxflow();
	cout << mflow << endl;
	
	for(int i = 0; i < mflow; i++){
		dfs(0);
		cout << ans.size() << endl;;
		cout << ans[0];
		for(int j = 1; j < ans.size(); j++) cout << " " << ans[j];
		cout << endl;
		ans.clear();
	}

	return 0;
}