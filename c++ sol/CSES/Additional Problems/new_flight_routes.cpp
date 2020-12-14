#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 100000;
int n, m;
int sc[maxn], tc[maxn];
bool used[maxn], d[maxn];
vector<int> graph[2][maxn];
vector<int> scc[maxn];
vector<int> it, ot, itt, ott;
stack<int> stk;
int s, t;
 
void dfs(int t, int c){
	used[c] = !t;
	for(int i : graph[t][c]){
		if(used[i] == !t) continue;
		dfs(t, i);
	}
	if(t){
		scc[s].push_back(c);
		sc[c] = s;
	}else stk.push(c);
}
 
int dfs2(int c){
	used[c]	= 1;
	bool t = 0;
	for(int i : scc[c])
	for(int j : graph[0][i]){
		if(sc[j] == c) continue;
		t = 1;
		if(used[sc[j]]) continue;
		int k = dfs2(sc[j]);
		if(k != -1) return k;
	}
	return !t ? c : -1;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		graph[0][u].push_back(v);
		graph[1][v].push_back(u);
	}
	
	for(int i = 0; i < n; i++) if(!used[i]) dfs(0, i);
	
	for(int i = 0; i < n; i++){
		int c = stk.top();
		stk.pop();
		if(used[c]){
			dfs(1, c);
			s++;
		} 
	}
	
	vector<pi> ans;
	for(int i = 0; i < s; i++){
		bool t = 0;
		for(int j : scc[i])
		for(int k : graph[0][j]){
			if(sc[k] == i) continue;
			t = d[sc[k]] = 1;
		}
		if(!used[i]){
			if(!d[i]){
				int j = dfs2(i);
				if(j != -1) it.push_back(scc[i][0]), ot.push_back(scc[j][0]);
				else itt.push_back(scc[i][0]);
			}else if(!t) ott.push_back(scc[i][0]);
		}
	}
	
	for(int i = 0; i < it.size() - 1; i++) ans.push_back({ot[i], it[i + 1]});
	for(int i = 0; i < min(itt.size(), ott.size()); i++) ans.push_back({ott[i], itt[i]});
	if(itt.size() < ott.size()) swap(itt, ott);
	for(int i = ott.size(); i < (int)itt.size() - 1; i++) ans.push_back({itt[i], itt[i + 1]});
	if(!itt.empty()){
		ans.push_back({ot.back(), itt[ott.size() % itt.size()]});
		ans.push_back({itt.back(), it[0]});
	}else if(s > 1){
		ans.push_back({ot.back(), it[0]});
	}

	cout << ans.size() << endl;
	for(pi i : ans) cout << i.f + 1 << " " << i.s + 1 << endl;
 
	return 0;
}