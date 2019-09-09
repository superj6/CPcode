#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;
#define endl '\n'
 
const int maxn = 200000;
int n;
int scc[maxn], tre[maxn];
bool used[maxn];
vector<int> graph[2][maxn];
int cycle[maxn];
int dep[maxn];
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
		scc[c] = s;
		cycle[s]++;
	}
}
 
void dfs2(int c, int p){
	tre[c] = p;
	used[c] = 1;
	for(int i : graph[1][c]){
		if(used[i] || scc[i] == scc[c]) continue;
		
		dep[i] = dep[c] + 1;
		dfs2(i, p);
	}
}

int ans(int i){
	return dep[i] + cycle[scc[tre[i]]];
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		graph[0][i].push_back(x);
		graph[1][x].push_back(i);
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
	
	memset(used, 0, sizeof(used));
	
	for(int i = 0; i < n; i++){
		if(cycle[scc[i]] == 1 && graph[0][i][0] != i) continue;
		dfs2(i, i);
	}
	
	cout << ans(0);
	for(int i = 1; i < n; i++) cout << " " << ans(i);
	cout << endl;
 
	return 0;
}