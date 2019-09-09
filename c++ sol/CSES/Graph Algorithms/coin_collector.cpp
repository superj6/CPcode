#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;
#define endl '\n'
 
const int maxn = 100000;
int n, m;
char ans[maxn];
bool used[maxn];
stack<int> stk;
vector<int> comp[maxn];
vector<int> graph[2][maxn];
int s;
long amt[maxn], val[maxn], scc[maxn];
 
void dfs(int c, int x){
	used[c] = 1;
	
	for(int i : graph[x][c]){
		if(!used[i]) dfs(i, x);
	}
	
	if(!x){
		stk.push(c);
	}else{
		scc[c] = s;
		comp[s].push_back(c);
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> val[i];
	
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
	
	long ans = 0;
	
	for(int c = 0; c < s; c++){
		for(int i : comp[c]){
			amt[c] += val[i];
		}
		
		ans = max(ans, amt[c]);
		
		for(int i : comp[c]){
			for(int j : graph[0][i]){
				amt[scc[j]] = max(amt[scc[j]], amt[c]);
			}
		}
	}
	
	cout << ans << endl;
 
	return 0;
}