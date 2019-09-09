#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 200000;
int n;
int sz[maxn];
vector<int> graph[maxn];

void dfs(int c){
	for(int i : graph[c]){
		dfs(i);
		sz[c] += sz[i] + 1;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 1; i < n; i++){
		int x;
		cin >> x;
		x--;
		graph[x].push_back(i);
	}
	
	dfs(0);
	
	cout << sz[0];
	for(int i = 1; i < n; i++) cout << " " << sz[i];
	cout << endl;

	return 0;
}