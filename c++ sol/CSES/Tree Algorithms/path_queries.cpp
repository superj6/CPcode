#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 200001;

struct BIT{
	long bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, int v){
		x++;
		for(; x < maxn; x += x & -x) bit[x] += v;
	}
 
	long qry(int x){
		long ret = 0;
		x++;
		for(; x > 0; x -= x & -x) ret += bit[x];
		return ret;
	}
	
	long qry(int a, int b){
		return qry(b) - qry(a - 1);
	}
};

int n, q;
BIT bit;
int l[maxn], r[maxn], v[maxn];
vector<int> graph[maxn];
int par[maxn], hev[maxn], hed[maxn];

int dfs1(int c){
	int sz = 1, msz = 0;
	hev[c] = -1;
	for(int i : graph[c]){
		if(i == par[c]) continue;
		par[i] = c;
		int nsz = dfs1(i);
		sz += nsz;
		if(nsz > msz){
			msz = nsz;
			hev[c] = i;
		}
	}
	return sz;
}

int dfs2(int c){
	r[c] = l[c];
	bit.add(l[c], v[c]);
	if(hev[c] != -1){
		l[hev[c]] = r[c] + 1;
		hed[hev[c]] = hed[c];
		r[c] = dfs2(hev[c]);
	}
	for(int i : graph[c]){
		if(i == par[c] || i == hev[c]) continue;
		l[i] = r[c] + 1;
		hed[i] = i;
		r[c] = dfs2(i);
	}
	return r[c];
}

long qry(int c){
	return bit.qry(l[hed[c]], l[c]) + (par[hed[c]] == -1 ? 0 : qry(par[hed[c]])); 
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++) cin >> v[i];
	
	for(int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	
	par[0] = -1;
	dfs1(0);
	dfs2(0);
	
	for(int i = 0; i < q; i++){
		int t, s;
		cin >> t >> s;
		s--;
		
		if(t == 1){
			int x;
			cin >> x;
			bit.add(l[s], x - v[s]);
			v[s] = x;
		}else{
			cout << qry(s) << endl;
		}
	}

	return 0;
}