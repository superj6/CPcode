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
int s = 0;

void dfs(int c, int x){
	used[c] = 1;
	for(int i : graph[x][c]){
		if(!used[i]) dfs(i, x);
	}
	
	if(!x){
		stk.push(c);
	}else{
		scc[c] = s + 1;
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
		s++;
	}
	
	cout << s << endl;
	cout << scc[0];
	for(int i = 1; i < n; i++) cout << " " << scc[i];
	cout << endl;

	return 0;
}