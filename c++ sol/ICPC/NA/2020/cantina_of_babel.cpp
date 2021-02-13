#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stack>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
int n, m;
int v[mxn];
map<string, int> f;
vector<int> g[2][mxn];
stack<int> stk;

int id(string &s){
	if(!f.count(s)) f[s] = m++;
	return f[s];
}

int dfs(int c, int t){
	v[c] = !t;
	int ret = c < n;
	for(int i : g[t][c]) if(v[i] == t) ret += dfs(i, t);
	if(!t) stk.push(c);
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	m = n;
	
	cin.ignore();
	for(int i = 0; i < n; i++){
		int x;
		string s;
		stringstream ss;
		getline(cin, s);
		ss << s;
		ss >> s >> s;
		
		x = id(s);
		for(int j = 0; j < 2; j++){
			g[j][i].push_back(x);
			g[j][x].push_back(i);
		}
		
		while(ss >> s){
			x = id(s);
			g[0][x].push_back(i);
			g[1][i].push_back(x);
		}
	}
	
	for(int i = 0; i < m; i++) if(!v[i]) dfs(i, 0);
	
	int ret = 0;
	while(!stk.empty()){
		int c = stk.top();
		stk.pop();
		if(v[c]) ret = max(ret, dfs(c, 1));
	}
	
	cout << (n - ret) << endl;
	
	return 0;
}