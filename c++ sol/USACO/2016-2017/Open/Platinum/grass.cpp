#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n, m, k, q;
int par[maxn], rankf[maxn];
map<int, int> graph[maxn];
pair<int, pair<int, int>> edges[maxn];

int field[maxn];
multiset<int> best;
multiset<int> bestn[maxn];
map<int, multiset<int>> colors[maxn];

int find(int x){
	return par[x] == x ? x : find(par[x]);
}

void unionf(int x, int y){
	if(rankf[x] < rankf[y]){
		swap(x, y);
	}else if(rankf[x] == rankf[y]){
		rankf[x]++;
	} 
	
	par[y] = x;
}

void dfs(int cur, int p){
	par[cur] = p;
	
	for(auto s : graph[cur]){
		if(s.first != par[cur]) dfs(s.first, cur);
	}
}

int main(){
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k >> q;
	
	for(int i = 0; i < n; i++){
		par[i] = i;
		rankf[i] = 0;
	}
	
	for(int i = 0; i < m; i++){
		cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
		edges[i].second.first--;
		edges[i].second.second--;
	}
	
	sort(edges, edges + m);
	
	for(int i = 0; i < m; i++){
		int x = find(edges[i].second.first), y = find(edges[i].second.second);
		
		if(x != y){
			unionf(x, y);
			graph[x][y] = edges[i].first;
			graph[y][x] = edges[i].first;
		}
	}
	
	dfs(0, -1);

	for(int i = 0; i < n; i++){
		cin >> field[i];
	}
	
	for(int i = 0; i < n; i++){
		for(auto s : graph[i]){
			if(s.first == par[i]) continue;
			colors[i][field[s.first]].insert(s.second);
		}
		
		for(auto s : colors[i]){
			if(s.first == field[i]) continue;
			bestn[i].insert(*s.second.begin());
		}
		
		if(bestn[i].size() > 0) best.insert(*bestn[i].begin());
	}
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--;
		
		if(field[a] == b){
			cout << *best.begin() << endl;
			continue;
		}
		
		if(bestn[a].size() > 0) best.erase(best.find(*bestn[a].begin()));
		if(colors[a][b].size() > 0) bestn[a].erase(bestn[a].find(*colors[a][b].begin()));
		if(colors[a][field[a]].size() > 0) bestn[a].insert(*colors[a][field[a]].begin());
		if(bestn[a].size() > 0) best.insert(*bestn[a].begin());
		
		
		if(par[a] != -1){
			
			if(bestn[par[a]].size() > 0){
				best.erase(best.find(*bestn[par[a]].begin()));
			}
			
			if(field[a] != field[par[a]]){
				bestn[par[a]].erase(bestn[par[a]].find(*colors[par[a]][field[a]].begin()));
			}
			
			colors[par[a]][field[a]].erase(colors[par[a]][field[a]].find(graph[a][par[a]]));
			
			if(field[a] != field[par[a]] && colors[par[a]][field[a]].size() > 0){
				bestn[par[a]].insert(*colors[par[a]][field[a]].begin());
			}
			
			if(b != field[par[a]] && colors[par[a]][b].size() > 0){
				bestn[par[a]].erase(bestn[par[a]].find(*colors[par[a]][b].begin()));
			}
			
			colors[par[a]][b].insert(graph[a][par[a]]);
			
			if(b != field[par[a]]){
				bestn[par[a]].insert(*colors[par[a]][b].begin());
			}
			
			if(bestn[par[a]].size() > 0) best.insert(*bestn[par[a]].begin());
		} 
		
		
		field[a] = b;
		
		cout << *best.begin() << endl;
	}

	return 0;
}