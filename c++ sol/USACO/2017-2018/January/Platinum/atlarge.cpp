#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

struct T{
	int st, ed, ss = 0;
	deque<int> dq;
	
	void add(int x, int v){
		if(dq.empty()){
			st = ed = x;
			ed++;
			dq.push_back(v);
		}else{
			while(x < st) dq.push_front(0), st--;
			while(x >= ed) dq.push_back(0), ed++;
			dq[x - st] += v;
		}
	}
	
	int qry(int x){
		return (dq.empty() || x < st ? 0 :
			x >= ed ? ss * dq[ed - st - 1] : dq[x - st]);
	}
	
	void ps(){
		ss = 1;
		for(int i = 1; i < ed - st; i++) dq[i] += dq[i - 1];
	}
	
	void clr(){
		ss = 0;
		dq.clear();
	}
};

const int mxn = 70000;
int n;
int d[mxn], sz[mxn], lf[mxn], vis[mxn];
vector<int> g[mxn];
queue<int> q;

T f;
vector<T> ff;
vector<vector<int>> v;
int ans[mxn];

int dfs(int c, int p){
	sz[c] = 1;
	for(int i : g[c]) if(i != p && !vis[i]) sz[c] += dfs(i, c);
	return sz[c];
}

int dfs2(int c, int p){
	for(int i : g[c]){
		if(i != p && !vis[i] && 2 * sz[i] > sz[c]){
			sz[i] = sz[c];
			return dfs2(i, c);
		}
	}
	return c;
}

void dfs3(int c, int p){
	int x = lf[c] - d[c], y = 2 - g[c].size();
	f.add(x, y);
	ff.back().add(x, y);
	v.back().push_back(c);
	
	for(int i : g[c]){
		if(i == p || vis[i]) continue;
		d[i] = d[c] + 1;
		dfs3(i, c);
	}
}

void sol(int c){
	dfs(c, -1);
	c = dfs2(c, -1);
	//
		d[c] = 0;
		f.clr();
		f.add(lf[c] - d[c], 2 - g[c].size());
		ff.clear();
		v.clear();
		
		for(int i : g[c]){
			if(vis[i]) continue;
			d[i] = d[c] + 1;
			ff.push_back(T());
			v.push_back(vector<int>());
			
			dfs3(i, c);
			ff.back().ps();
		}
		f.ps();
		
		ans[c] += f.qry(d[c]);
		for(int i = 0; i < v.size(); i++)
		for(int j : v[i]){
			ans[j] += f.qry(d[j]) - ff[i].qry(d[j]);
		}
	//
	vis[c] = 1;
	for(int i : g[c]) if(!vis[i]) sol(i);
}

int main(){
	freopen("atlarge.in", "r", stdin);
	freopen("atlarge.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	memset(lf, -1, sizeof(lf));
	for(int i = 0; i < n; i++){
		if(g[i].size() <= 1){
			lf[i] = 0;
			ans[i]--;
			q.push(i);
		} 
	}
	
	while(!q.empty()){
		int c = q.front();
		q.pop();
		for(int i : g[c]){
			if(!~lf[i]){
				lf[i] = lf[c] + 1;
				q.push(i);
			}
		}
	}
	
	sol(0);
	
	for(int i = 0; i < n; i++) cout << ans[i] << endl;

	return 0;
}