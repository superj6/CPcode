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

const int mxn = 2000;
int n, k;
int a[mxn], b[mxn], dp[mxn], f[mxn], vis[mxn];
vector<int> g[2][mxn], v[mxn];
stack<int> s;

void dfs(int c, int t){
	vis[c] = !t;
	for(int i : g[t][c]) if(vis[i] == t) dfs(i, t);
	if(t) b[c] = v[a[c] = k].size(), v[k].push_back(c);
	else s.push(c);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i < n; i++)
	for(int j = 0; j < i; j++){
		int t, x = i, y = j;
		cin >> t;
		if(t) swap(x, y);
		g[0][x].push_back(y);
		g[1][y].push_back(x);
	}
	
	for(int i = 0; i < n; i++) if(!vis[i]) dfs(i, 0);
	
	while(!s.empty()){
		int c = s.top();
		s.pop();
		if(vis[c]) dfs(c, 1), k++;
	}
	
	for(int i = k - 1; ~i; i--){
		f[i] = -1;
		for(int j : v[i])
		for(int l : g[0][j]){
			if(dp[i] < dp[a[l]]) dp[i] = dp[a[l]], f[i] = a[l];
		}
		dp[i] += v[i].size();
	}
	
	for(int i = 0; i < n; i++){
		cout << dp[a[i]];
		for(int j = a[i], l = b[i]; ~j; j = f[j], l = 0)
		for(int p = 0, m = v[j].size(); p < m; p++){
			cout << " " << (v[j][(l + p) % m] + 1);
		}
		cout << endl;
	}
	
	return 0;
}