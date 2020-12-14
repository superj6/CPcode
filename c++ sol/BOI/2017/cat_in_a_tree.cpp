#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 200000;
int n, m;
vector<int> graph[maxn];
 
pi dfs(int c){
	if(graph[c].empty()) return {1, 1};
	pi ret = dfs(graph[c][0]);
	if(ret.s == m) ret.f++, ret.s = 0;
	for(int i = 1; i < graph[c].size(); i++){
		pi p = dfs(graph[c][i]);
		if(ret.s + p.s >= m) ret.f += p.f, ret.s = min(ret.s, p.s);
		else ret.f += p.f - 1, ret.s = max(ret.s, p.s);
	}
  	ret.s++;
	return ret;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 1; i < n; i++){
		int x;
		cin >> x;
		graph[x].push_back(i);
	}
	
	cout << dfs(0).f << endl;
 
	return 0;
}