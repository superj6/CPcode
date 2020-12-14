#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const int mxn = 1000000;
int n;
int a[mxn], f1[mxn], f2[mxn];
vector<int> g[mxn];

void upd(int x, int v){
	f2[x] = max(f2[x], v);
	if(f2[x] > f1[x]) swap(f1[x], f2[x]);
}

void dfs(int c, int p){
	for(int i : g[c]){
		if(i == p) continue;
		dfs(i, c);
		if(!~-a[i]) upd(c, f1[i] + 1);
	}
}

void dfs2(int c, int p){
	for(int i : g[c]){
		if(i == p) continue;
		if(!~-a[c]) upd(i, (f1[i] + 1 == f1[c] ? f2[c] : f1[c]) + 1);
		dfs2(i, c);
	} 
}

int main(){
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
	for(int i = 0; i < n; i++) cin >> a[i];
	
	dfs(0, -1);
	dfs2(0, -1);
	
	ll x = 1, y = 0;
	for(int i = 0; i < n; i++){
		ll w = a[i], z = f1[i] + f2[i] + 1;
		if(w * y < x * z) x = w, y = z;
	}
	ll g = __gcd(x, y);
	x /= g, y /= g;
	
	cout << x << "/" << y << endl;

	return 0;
}