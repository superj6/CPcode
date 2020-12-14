#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

const ll inf = 0x3f3f3f3f3f3f3f3f, inf2 = inf >> 2;

struct segTree{
	int l, r;
	segTree *left, *right;
	ll val = inf, lzy = 0;
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	ll amt(){
		return val + lzy;
	}
	
	void push(){
		val += lzy;
		left->lzy += lzy;
		right->lzy += lzy;
		lzy = 0;
	}
	
	void add(int a, int b, ll v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lzy += v;
			return;
		}
		push();
		left->add(a, b, v);
		right->add(a, b, v);
		val = min(left->amt(), right->amt());
	}
	
	ll qry(int a, int b){
		if(b < l || r < a) return inf;
		if(a <= l && r <= b) return amt();
		push();
		return min(left->qry(a, b), right->qry(a, b));
	}
};

const int mxn = 100000;
int n, m, k, q;
pii e[mxn];
ll a[mxn], d[mxn], l[mxn], r[mxn];
vector<int> g[mxn];
vector<pi> qr[mxn];
segTree tre(0, mxn);
ll ans[mxn];

int dfs(int c, int p){
	r[c] = l[c];
	if(a[c] && k != c) tre.add(l[c], l[c], d[c] - inf);
	for(int i : g[c]){
		if(i == p) continue;
		if(c != e[i].s.f) swap(e[i].s.f, e[i].s.s);
		d[e[i].s.s] = d[c] + e[i].f;
		l[e[i].s.s] = r[c] + 1;
		r[c] = dfs(e[i].s.s, i);
	}
	return r[c];
}

void dfs2(int c, int p){
	for(pi i : qr[c]){
		ans[i.s] = (l[e[i.f].s.s] <= l[c] && l[c] <= r[e[i.f].s.s]) ?
			tre.qry(l[e[i.f].s.s], r[e[i.f].s.s]) :
			min(tre.qry(0, l[e[i.f].s.s] - 1), tre.qry(r[e[i.f].s.s] + 1, n - 1));
	}
	for(int i : g[c]){
		if(i == p) continue;
		tre.add(0, n - 1, e[i].f);
		tre.add(l[e[i].s.s], r[e[i].s.s], -2 * e[i].f);
		dfs2(e[i].s.s, i);
		tre.add(0, n - 1, -e[i].f);
		tre.add(l[e[i].s.s], r[e[i].s.s], 2 * e[i].f);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q >> k;
	k--;
	
	for(int i = 0; i < n - 1; i++){
		cin >> e[i].s.f >> e[i].s.s >> e[i].f;
		g[--e[i].s.f].push_back(i);
		g[--e[i].s.s].push_back(i);
	}
	
	for(int i = 0; i < m; i++){
		int x;
		cin >> x;
		a[--x] = 1;
	}
	
	dfs(0, -1);
	tre.add(l[k], l[k], -2 * inf);
	
	for(int i = 0; i < q; i++){
		int x, y;
		cin >> y >> x;
		qr[--x].push_back({--y, i});
	}
	
	dfs2(0, -1);
	
	for(int i = 0; i < q; i++){
		cout << (ans[i] < -inf2 ? "escaped" : ans[i] > inf2 ? "oo" : to_string(ans[i])) << endl;
	}

	return 0;
}