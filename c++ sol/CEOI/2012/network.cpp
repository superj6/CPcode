#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100000;
int n, m, k;
int sc[maxn], sz[maxn], p[maxn];
bool used[maxn];
vector<int> scc[maxn];
vector<int> graph[2][maxn];
stack<int> stk;
vector<pi> ans;
int s;

void dfs(int c, int t){
	used[c] = !t;
	for(int i : graph[t][c]){
		if(used[i] == t) dfs(i, t);
	}
	if(!t){
		stk.push(c);
	}else{
		sc[c] = s;
		scc[s].push_back(c);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[0][u].push_back(v);
		graph[1][v].push_back(u);
	}
	
	for(int i = 0; i < n; i++) if(!used[i]) dfs(i, 0);
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		if(used[c]){
			dfs(c, 1);
			s++;
		}
	}
	
	for(int i = s - 1; ~i; i--)
	for(int j : scc[i]){
		sz[i]++, p[j] = -1;
		bool t = 0;
		for(int l : graph[0][j]){
			if(sc[l] != i){
				sz[i] += sz[sc[l]];
				if(!~p[j]) p[j] = p[l];
				else ans.push_back({p[l], j});
			} 
		}
		for(int l : graph[1][j]) t |= sc[l] != i;
		if(!~p[j]) p[j] = j;
		else if(!t) ans.push_back({p[j], j});
	}
	
	cout << sz[sc[0]];
	for(int i = 1; i < n; i++) cout << " " << sz[sc[i]];
	cout << endl;
	
	cout << ans.size() << endl;
	for(pi i : ans) cout << i.f + 1 << " " << i.s + 1 << endl;

	return 0;
}