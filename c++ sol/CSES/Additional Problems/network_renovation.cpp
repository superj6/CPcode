#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n;
vector<int> graph[maxn];
vector<int> lf;

void dfs(int c, int p){
	if(graph[c].size() == 1) lf.push_back(c + 1);
	for(int i : graph[c]){
		if(i == p) continue;
		dfs(i, c);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	dfs(0, -1);
	
	int k = (lf.size() + 1) / 2;
	cout << k << endl;
	for(int i = 0; i < k; i++) cout << lf[i] << " " << lf[i + lf.size() / 2] << endl;

	return 0;
}