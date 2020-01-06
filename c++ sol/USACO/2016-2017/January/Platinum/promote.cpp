/*
	This problem is a very simple problem of given a tree count the number of nodes in its subtree with a value greater than it. You
can simply sort the nodes by value in reverse order and relable them with an euler tour, then iterate through the sorted nodes and add
them to a BIT as you iterate, then query the the amount of nodes previously added within the subtree of the current node. The commplexity
of this is O(nlogn) from BIT operations.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

vector<int> graph[100000];
pair<int, int> r[100000];
int cnt = 0;
int n;

void dfs(int cur){
	r[cur].first = cnt;
	
	for(int i = 0; i < graph[cur].size(); i++){
		dfs(graph[cur][i]);
	}
	
	r[cur].second = cnt;
	cnt++;
}

int bit[100001];

void add(int x){
	x++;
	
	for(; x <= n; x += x & (-x)) bit[x]++;
}

int qry(int x){
	x++;
	int ret = 0;
	
	for(; x > 0; x -= x & (-x)) ret += bit[x];
	
	return ret;
}

int main(){
	freopen("promote.in", "r", stdin);
	freopen("promote.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	pair<int, int> a[n];
	for(int i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].second = i;
		bit[i] = 0;
	}
	
	sort(a, a + n, greater<pair<int, int>>());
	
	for(int i = 1; i < n; i++){
		int x;
		cin >> x;
		x--;
		
		graph[x].push_back(i);
	}
	
	dfs(0);
	
	int ans[n];
	
	for(int i = 0; i < n; i++){
		int cur = a[i].second;
		ans[cur] = qry(r[cur].second) - qry(r[cur].first - 1);
		add(r[cur].second);
	}
	
	for(int i = 0; i < n; i++) cout << ans[i] << endl;

	return 0;
}
