#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <string.h>
#include <tuple>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

vector<int> v;
struct segTree{
	int l, r;
	segTree *left, *right;
	set<pi> s;
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void add(int x, int y, int id){
		if(x < l || r < x) return;
		if(!s.count({y, id})) s.insert({y, id});
		else s.erase({y, id});
		if(l == r) return;
		left->add(x, y, id);
		right->add(x, y, id);
	}
	
	void qry(int x, int X, int y, int Y){
		if(X < l || r < x) return;
		if(x <= l && r <= X){
			for(auto it = s.lower_bound({y, -1}); it != s.end() && it->f <= Y; it++){
				v.push_back(it->s);
			}
			return;
		}
		left->qry(x, X, y, Y);
		right->qry(x, X, y, Y);
	}
};

typedef tuple<int, int, int, int, int> T;

const int mxn = 70000, mxm = 150000;
int n, m, w, h;
int x[mxn], y[mxn];
int t[mxm], l[mxm], r[mxm], d[mxm], u[mxm];
int dst[mxn];
vector<int> g[mxn];
priority_queue<T, vector<T>, greater<T>> pq;
segTree tre(1, mxn);

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> w >> h;
	
	for(int i = 0; i < n; i++){
		cin >> x[i] >> y[i];
		tre.add(x[i], y[i], i);
	} 
	for(int i = 0; i < m; i++){
		int x;
		cin >> x >> t[i] >> l[i] >> r[i] >> d[i] >> u[i];
		g[--x].push_back(i);
	}
	
	memset(dst, 0x3f, sizeof(dst));
	pq.push({0, x[0], x[0], y[0], y[0]});
	while(!pq.empty()){
		int cdst, cl, cr, cd, cu;
		tie(cdst, cl, cr, cd, cu) = pq.top();
		pq.pop();
		v.clear();
		tre.qry(cl, cr, cd, cu);
		for(int c : v){
			dst[c] = cdst;
			tre.add(x[c], y[c], c);
			for(int i : g[c]) pq.push({cdst + t[i], l[i], r[i], d[i], u[i]});
		}
	}
	
	for(int i = 1; i < n; i++) cout << dst[i] << endl;

	return 0;
}