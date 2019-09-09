#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'

const int maxn = 100000;
int n, m;
int s = 1, sz = 0;
int scc[maxn];
bool visited[maxn];
stack<int> stk;
vector<int> ans;
vector<int> graph[2][maxn];

int dfs(int c, int d){
	visited[c] ^= 1;
	
	for(int i : graph[d & 1][c]){
		if(visited[i] ^ (d & 1)){
			if(d == 2 && scc[i] == s){
				ans.push_back(i + 1);
				ans.push_back(c + 1);
				return i;
			}
			
			continue;
		} 
		
		int t = dfs(i, d);
		if(t != -1){
			if(t != n){
				ans.push_back(c + 1);
				if(t == c) t = n;
			}
			
			return t;
		}
	}
	
	if(d == 0){
		stk.push(c);
	}else if(d == 1){
		scc[c] = s;
		sz++;
	}
	
	return -1;
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
		if(!visited[i]) dfs(i, 0);
	}
	
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		
		if(!visited[c]) continue;
		
		dfs(c, 1);
		
		if(sz > 1){
			dfs(c, 2);
			
			reverse(ans.begin(), ans.end());
			
			cout << ans.size() << endl;
			cout << ans[0];
			for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
			cout << endl;
			
			
			return 0;
		}
		
		s++;
		sz = 0;
	}
	
	cout << "IMPOSSIBLE" << endl;

	return 0;
}