#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 50000;
int n, k, maxv = 0;
int amt[maxn], ancestor[maxn], parent[maxn], rankf[maxn], prevf[maxn];
bool visited[maxn];

vector<int> graph[maxn], query[maxn];

int find(int x){
	return parent[x] == x ? x : find(parent[x]);
}

void unionf(int x, int y){
	x = find(x);
	y = find(y);
	
	if(x == y) return;
	
	if(rankf[x] < rankf[y]){
		x = x + y;
		y = x - y;
		x = x - y;
	}
	
	parent[y] = x;
	if(rankf[x] == rankf[y]) rankf[x]++;
}

void dfsq(int cur){
	visited[cur] = true;
	amt[cur] += query[cur].size();
	
	for(int i = 0; i < query[cur].size(); i++){
		if(visited[query[cur][i]]){
			amt[ancestor[find(query[cur][i])]]--;
			if(ancestor[find(query[cur][i])] != 0) amt[prevf[ancestor[find(query[cur][i])]]]--;
		} 
	}
	
	for(int i = 0; i < graph[cur].size(); i++){
		if(!visited[graph[cur][i]]){
			prevf[graph[cur][i]] = cur;
			dfsq(graph[cur][i]);
			unionf(cur, graph[cur][i]);
			ancestor[find(cur)] = cur;		
		}
	}
	
}

int dfsa(int cur){
	visited[cur] = true;
	int sum = amt[cur];
	
	for(int i = 0; i < graph[cur].size(); i++){
		if(!visited[graph[cur][i]]){
			sum += dfsa(graph[cur][i]);
		}
	}
	
	maxv = max(maxv, sum);
	
	return sum;
}

int main(){
	freopen("maxflow.in", "r", stdin);
	freopen("maxflow.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		amt[i] = 0;
		ancestor[i] = i;
		parent[i] = i;
		rankf[i] = 0;
		visited[i] = false;
		
		if(i == 0) continue;
		
		int x, y;
		cin >> x >> y;
		x--, y--;
		
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	for(int i = 0; i < k; i++){
		int s, t;
		cin >> s >> t;
		s--, t--;
		
		query[s].push_back(t);
		query[t].push_back(s);
	}
	
	dfsq(0);
	
	for(int i = 0; i < n; i++) visited[i] = false;
	
	dfsa(0);
	
	cout << maxv << endl;
	
	return 0;
}