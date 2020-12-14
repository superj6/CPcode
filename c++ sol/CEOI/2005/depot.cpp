#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>
 
const int mxn = 400;
int n, m, k;
vi g[mxn << 1];
vi v[mxn][mxn];
vi ans;
 
void dfs(int c){
	while(!g[c].empty()){
		int x = g[c].back();
		g[c].pop_back();
		dfs(x);
		if(c < n){
			ans.push_back(v[c][x - n].back() + 1);
			v[c][x - n].pop_back();
		}
	}
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n * m; i++){
		int x;
		cin >> x;
		v[i / m][--x].push_back(i);
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		if(v[i][j].empty()) g[n + j].push_back(i);
		for(int l = 1; l < v[i][j].size(); l++) g[i].push_back(n + j);
	}
	
	for(int i = 0; i < n; i++){
		if(!g[i].empty()){
			ans.push_back(n * m + 1);
			dfs(i);
		} 
	}
	ans.push_back(n * m + 1);
	
	k = ans.size();
	cout << k - 1 << endl;
	for(int i = 0; i < k - 1; i++) cout << ans[i + 1] << " " << ans[i] << endl;
 
	return 0;
}