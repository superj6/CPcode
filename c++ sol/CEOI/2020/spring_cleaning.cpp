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

struct segTree{
	int l, r;
	segTree *left, *right;
	int v0 = 1, v1 = 0, lz = 0;
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
			pull();
		}
	}
	
	void upd(){
		lz ^= 1;
		swap(v0, v1);
	}
	
	void push(){
		if(lz) left->upd(), right->upd();
		lz = 0;
	}
	
	void pull(){
		v0 = left->v0 + right->v0;
		v1 = left->v1 + right->v1;
	}
	
	void add(int a, int b){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			upd();
			return;
		}
		push();
		left->add(a, b);
		right->add(a, b);
		pull();
	}
};

const int mxn = 200000;
int n, m, k, q;
int p[mxn], d[mxn], sz[mxn], h[mxn], l[mxn], r[mxn];
vector<int> v;
vector<int> g[mxn];
segTree *tre;

int dfs(int c){
	sz[c] = 1;
	if(~p[c]) g[c].erase(find(g[c].begin(), g[c].end(), p[c]));
	for(int &i : g[c]){
		p[i] = c;
		sz[c] += dfs(i);
		if(sz[i] > sz[g[c][0]]) swap(i, g[c][0]);
	}
	return sz[c];
}

int dfs2(int c){
	r[c] = l[c];
	for(int i : g[c]){
		h[i] = (i == g[c][0] ? h[c] : i);
		l[i] = r[c] + 1;
		r[c] = dfs2(i);
	}
	return r[c];
}

void add(int x){
	for(; ~x; x = p[h[x]]) tre->add(l[h[x]], l[x]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin >> u >> v;
		d[--u]++, d[--v]++;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	p[0] = -1;
	dfs(0);
	dfs2(0);
	
	tre = new segTree(0, n - 1);
	for(int i = 0; i < n; i++) if(d[i] <= 1) add(i), m++;
	
	while(q--){
		cin >> k;
		m += k;
		v.resize(k);
		for(int i = 0; i < k; i++){
			cin >> v[i];
			if(!~-(d[--v[i]]++)) m--;
			else add(v[i]);
		}
		
		cout << (m & 1 ? -1 : n + k + tre->v0 - 2) << endl;
		
		m -= k;
		for(int i : v){
			if(!~-(--d[i])) m++;
			else add(i);
		}
	}

	return 0;
}