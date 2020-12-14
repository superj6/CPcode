#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
int scc[maxn], ind[maxn], dp2[maxn];
int dp[2][maxn];
bool used[maxn];
vector<int> graph[2][maxn];
vector<int> cycle[maxn];
stack<int> stk;
map<string, int> mp;
int m, s, p;

int id(string x){
	if(mp.find(x) == mp.end()) mp[x] = m++;
	return mp[x];
}

void dfs(int c, int x){
	used[c] = 1;
	for(int i : graph[x][c]){
		if(!used[i]) dfs(i, x);
	}
	
	if(!x){
		stk.push(c);
	}else{
		scc[c] = s;
		ind[c] = cycle[s].size();
		cycle[s].push_back(c);
	}
}

void dfs2(int c){
	dp[1][c] = -n;
	for(int i : graph[1][c]){
		if(scc[i] == scc[c]) continue;
		dfs2(i);
		dp[0][c] += dp[1][i];
		dp[1][c] = max(dp[1][c], dp[0][i] - dp[1][i]);
	}
	dp[1][c] = dp[0][c] + max(0, 1 + dp[1][c]);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int u, v;
		string x, y;
		cin >> x >> y;
		u = id(x), v = id(y);
		graph[0][u].push_back(v);
		graph[1][v].push_back(u);
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
	
	int ret = n;
	for(int i = 0; i < s; i++){
		if(cycle[i].size() == 1 && graph[0][cycle[i][0]][0] != cycle[i][0]) continue;
		for(int j : cycle[i]) dfs2(j);
		int cur = (cycle[i].size() == 2 ? 2 + dp[0][cycle[i][0]] + dp[0][cycle[i][1]] : 0);
		for(int t = 0; t < 2; t++){
			memset(dp2, 0, cycle[i].size() * sizeof(int));
			for(int j = 0; j < cycle[i].size(); j++){
				dp2[j] = max(dp2[j], dp[1][cycle[i][(j + t) % cycle[i].size()]] + (j ? dp2[j - 1] : 0));
				if(j) dp2[j] = max(dp2[j], 1 + dp[0][cycle[i][(j + t) % cycle[i].size()]] + dp[0][cycle[i][(j + t - 1) % cycle[i].size()]] + (j > 1 ? dp2[j - 2] : 0));
			}
			cur = max(cur, dp2[cycle[i].size() - 1]);
		}
		ret -= cur;
	}
	
	cout << (n & 1 ? -1 : ret) << endl;

	return 0;
}