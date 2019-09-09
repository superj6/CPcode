#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n, m;
int scc[maxn];
bool used[maxn];
vector<int> graph[2][maxn];
stack<int> stk;
int s = 0, f = -1;

void dfs(int c, int x){
	used[c] = 1;
	for(int i : graph[x][c]){
		if(!used[i]) dfs(i, x);
	}
	
	if(!x){
		stk.push(c);
	}else{
		scc[c] = s;
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
		
		graph[0][a].push_back(b);
		graph[1][b].push_back(a);
	}
	
	for(int i = 0; i < n; i++){
		if(!used[i]) dfs(i, 0);
	}
	
	memset(used, 0, sizeof(used));
	
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		
		if(used[c]) continue;
		dfs(c, 1);
		
		if(f == -1){
			f = c;
		}else{
			cout << "NO" << endl;

			memset(used, 0, sizeof(used));
			queue<int> q;
			q.push(c);
			
			while(!q.empty()){
				int d = q.front();
				q.pop();
				
				
				for(int i : graph[0][d]){
					if(used[i]) continue;
					
					if(scc[i] != s){
						cout << i + 1 << " " << c + 1 << endl;
						return 0;
					}
					
					used[i] = 1;
					q.push(i);
				}
				
			}
			
			cout << c + 1 << " " << f + 1 << endl;
			return 0;
		}
		
		s++;
	}
	
	cout << "YES" << endl;

	return 0;
}