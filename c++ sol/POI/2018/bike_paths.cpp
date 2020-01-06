#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 50000;
int n, m, s;
int id[maxn], dp[maxn];
bool used[maxn];
vector<int> graph[maxn], rgraph[maxn], scc[maxn];
vector<int> stk;

void dfs(int c, bool t){
	used[c] = t;
	for(int i : (t ? graph[c] : rgraph[c])){
		if(used[i] == t) continue;
		dfs(i, t);
	}
	if(t){
		stk.push_back(c);
	}else{
		id[c] = s;
		scc[s].push_back(c);
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
		graph[a].push_back(b);
		rgraph[b].push_back(a);
	}
	
	for(int i = 0; i < n; i++){
		if(!used[i]) dfs(i, 1);
	}
	
	reverse(stk.begin(), stk.end());
	
	for(int i : stk){
		if(used[i]){
			dfs(i, 0);
			s++;
		}
	}
	
	for(int i = s - 1; i >= 0; i--){
		dp[i] += scc[i].size();
		for(int j : scc[i]){
			for(int l : rgraph[j]){
				dp[id[l]] += dp[i] * (id[l] != i);
			}
		}
	}
	
	for(int i = 0; i < n; i++) cout << (dp[id[i]] - 1) << endl;

	return 0;
}