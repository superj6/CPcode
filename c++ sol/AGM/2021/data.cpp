#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second
 
const int inf = 0x3f3f3f3f;
 
struct lcTree{
	int n, m;
	vector<unordered_map<int, int>> e;
	struct node{
		int p = 0, pp = 0, b = 0, sz = 0, vsz = 0;
		int c[2] = {0, 0};
		pii val = {inf, {0, 0}}, dp = {inf, {0, 0}};
	};
	vector<node> T;
 
	lcTree(int N) : n(N), m(n), T(n + 1), e(n + 1) {}
 
	//splay
	int dir(int x, int y){
		return T[x].c[1] == y;
	}
 
	void pull(int x){
		if(!x) return;
		int l = T[x].c[0], r = T[x].c[1];
		T[x].dp = min({T[x].val, T[l].dp, T[r].dp});
		T[x].sz = T[l].sz + T[r].sz + T[x].vsz + (x <= n);
	}
 
	void set(int x, int y, int d){
		if(x) T[x].c[d] = y, pull(x);
		if(y) T[y].p = x;
	}
 
	void push(int x){
		if(!x || !T[x].b) return;
		int &l = T[x].c[0], &r = T[x].c[1];
		swap(l, r);
		T[l].b ^= 1, T[r].b ^= 1;
		T[x].b = 0;
	}
 
	void rotate(int x, int d){
		int y = T[x].p, z = T[y].p, w = T[x].c[d];
		swap(T[x].pp, T[y].pp);
		set(y, w, !d);
		set(x, y, d);
		set(z, x, dir(z, y));
	}
 
	void splay(int x){
		for(push(x); T[x].p;){
			int y = T[x].p, z = T[y].p;
			push(z), push(y), push(x);
			int dx = dir(y, x), dy = dir(z, y);
			if(!z) rotate(x, !dx);
			else if(dx == dy) rotate(y, !dx), rotate(x, !dx);
			else rotate(x, dy), rotate(x, dx);
		}
	}
	//splay end
 
	void access(int x){
		for(int v = 0, u = x; u; u = T[v = u].pp){
			splay(u), splay(v);
			int r = T[u].c[1];
			T[v].pp = 0;
			swap(T[r].p, T[r].pp);
			T[u].vsz -= T[v].sz;
			T[u].vsz += T[r].sz;
			set(u, v, 1);
		}
		splay(x);
	}
 
	void mkroot(int x){
		access(x);
		int l = T[x].c[0];
		T[l].b ^= 1;
		swap(T[l].p, T[l].pp);
		T[x].vsz += T[l].sz;
		set(x, 0, 0);
	}
 
	void link(int u, int v, int x = inf){
		if(u > v) swap(u, v);
		if(!e[u][v]){
			e[u][v] = T.size();
			T.push_back(node());
		} 
		int w = e[u][v];
		T[w].val = {x, {u, v}};
		mkroot(v);//, access(u);
		T[v].pp = w, T[w].pp = u;
		T[w].vsz += T[v].sz, T[u].vsz += T[v].sz;
		m--;
	}
 
	void cut(int u, int v){
		if(u > v) swap(u, v);
		int w = e[u][v];
		mkroot(w), access(w), mkroot(u), access(u), splay(v);
		T[v].pp = T[w].pp = 0;
		T[w].vsz -= T[v].sz, T[u].vsz -= T[v].sz;
		m++;
	}
 
	bool connected(int u, int v){
		mkroot(u), access(v), splay(u);
		return u == v || T[v].p == u || T[T[v].p].p == u;
	}
 
	bool pathcon(int u, int v){
		if(u > v) swap(u, v);
		return connected(u, e[u][v]);
	}
 
	pii pathval(int u, int v){
		if(!connected(u, v)) return {-1, {0, 0}};
		mkroot(u), access(v);
		return T[v].dp;
	}
 
	int subsz(int rt, int x){
		mkroot(rt), access(x);
		return T[x].vsz + 1;
	}
};
 
const ll mod = 1000000007;
const int mxn = 300005;
ll n, m, k, q;
ll a[mxn];
pii qry[mxn];
set<pi> s;
unordered_map<int, int> mp[mxn];
int bf[mxn];
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> m >> q >> k;
	k++;
 
	a[0] = 1;
	for(int i = 1; i <= n; i++) a[i] = (__int128)k * a[i - 1] % mod;
 
	for(int i = 0; i < m + q; i++){
		int u, v;
		cin >> u >> v;
		if(u > v) swap(u, v);
		if(s.count(qry[i].s = {u, v})){
			qry[i].f = 1;
			s.erase(qry[i].s);
		}else{
			s.insert(qry[i].s);
		}
	}
	lcTree tre(n);
    for(int i = m+q-1; i >= 0; i--){
        int u = qry[i].s.f, v = qry[i].s.s;
		if(!qry[i].f){
			bf[i] = (mp[u].find(v) == mp[u].end() ? inf : mp[u][v]);
		}else{
            mp[u][v] = i;
		}
    }
   
	for(int i = 0; i < m+q; i++){
		int u = qry[i].s.f, v = qry[i].s.s;
		if(!qry[i].f){
			pii x = tre.pathval(u, v);
			int z = bf[i];
			if(x.f < z){
				if(x.s.f) tre.cut(x.s.f, x.s.s);
				tre.link(u, v, z);
			} 
		}else{
			if(tre.pathcon(u, v)) tre.cut(u, v);
		}
		if(i >= m - 1) cout << a[n - tre.m] << endl;
	}
 
	return 0;
}
