#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

struct lcTree{
	struct node{
		int p = 0, pp = 0, b = 0, val = 0, dp = 0;
		int c[2] = {0, 0};
	};
	vector<node> T;
	
	lcTree(int n) : T(n + 1) {}
	
	//splay
	int dir(int x, int y){
		return T[x].c[1] == y;
	}
	
	void pull(int x){
		if(!x) return;
		int l = T[x].c[0], r = T[x].c[1];
		T[x].dp = T[x].val + T[l].dp + T[r].dp;
	}
	
	void set(int x, int y, int d){
		if(x) T[x].c[d] = y, pull(x);
		if(y) T[y].p = x;
	}
	
	void push(int x){
		if(!x || !T[x].b) return;
		int &l = T[x].c[0], &r = T[x].c[1];
		swap(l, r);
		T[x].b = 0, T[l].b ^= 1, T[r].b ^= 1;
	}
	
	void rotate(int x, int d){
		int y = T[x].p, z = T[y].p, w = T[x].c[d];
		swap(T[x].pp, T[y].pp);
		set(y, w, !d), set(x, y, d), set(z, x, dir(z, y));
	}
	
	void splay(int x){
		for(push(x); T[x].p; ){
			int y = T[x].p, z = T[y].p;
			push(z), push(y), push(x);
			int dx = dir(y, x), dy = dir(z, y);
			if(!z) rotate(x, !dx);
			else if(dx == dy) rotate(y, !dx), rotate(x, !dy);
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
			set(u, v, 1);
		}
		splay(x);
	}
	
	void mkroot(int x){
		access(x);
		int l = T[x].c[0];
		T[l].b ^= 1;
		swap(T[l].p, T[l].pp);
		set(x, 0, 0);
	}
	
	void link(int u, int v){
		mkroot(v);
		T[v].pp = u;
	}
	
	void cut(int u, int v){
		mkroot(u), splay(v);
		T[v].pp = 0;
	}
	
	bool connected(int u, int v){
		mkroot(u), access(v), splay(u);
		return u == v || T[v].p == u || T[T[v].p].p == u;
	}
	
	int pathval(int u, int v){
		mkroot(u), access(v);
		return T[v].dp;
	}
	
	void setval(int u, int v){
		access(u);
		T[u].val = v;
	}
};

const int mxn = 30000;
int n, q;
lcTree tre(mxn);

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		tre.setval(i, x);
	}
	
	cin >> q;
	
	for(int i = 0; i < q; i++){
		string s;
		int x, y;
		cin >> s >> x >> y;
		
		if(s == "penguins"){
			tre.setval(x, y);
		}else if(s == "bridge"){
			if(tre.connected(x, y)){
				cout << "no" << endl;
			}else{
				cout << "yes" << endl;
				tre.link(x, y);
			}
		}else{
			if(tre.connected(x, y)) cout << tre.pathval(x, y) << endl;
			else cout << "impossible" << endl;
		}
	}

	return 0;
}