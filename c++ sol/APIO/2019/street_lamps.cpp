#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

const int maxn = 300000;

struct segTree{
	int l, r;
	segTree *left = NULL, *right = NULL;
	long val = 0, lazy = 0;
 
	segTree(int a, int b){
		l = a;
		r = b;
	}
	
	void push(){
		if(left) left->lazy += lazy;
		if(right) right->lazy += lazy;
		lazy = 0;
	}
	
	void set(int x, int v){
		if(l == r){
			val = v;
			lazy = 0;
			return;
		}
 
		push();
		
		int mid = (l + r) / 2;
		if(x <= mid){
			if(!left) left = new segTree(l, mid);
			left->set(x, v);
		}
		if(x > mid){
			if(!right) right = new segTree(mid + 1, r);
			right->set(x, v);
		}
	}
 
	void add(int a, int b, int v){
		if(a <= l && r <= b){
			lazy += v;
			return;
		}
 
		push();
		
		int mid = (l + r) / 2;
		if(left && a <= mid) left->add(a, b, v);
		if(right && b > mid) right->add(a, b, v);
	}
 
	long qry(int x){
		if(l == r) return val + lazy;
		push();
		int mid = (l + r) / 2;
		if(left && x <= mid) return left->qry(x);
		if(right && x > mid) return right->qry(x);
		return -1;
	}
};

struct segTree2d{
	int l, r;
	segTree2d *left = NULL, *right = NULL;
	segTree *val = NULL;
	vector<pii> lazy;
 
	segTree2d(int a, int b){
		l = a;
		r = b;
	}
	
	void push(){
		for(pii i : lazy){
			if(left) left->lazy.push_back(i);
			if(right) right->lazy.push_back(i);
			if(val) val->add(i.s.f, i.s.s, i.f);
		}
		lazy.clear();
		
	}
	
	void set(int x, int y, int v){
		push();
		if(l == r){
			if(!val) val = new segTree(0, maxn);
			val->set(y, v);
			return;
		}
		
		int mid = (l + r) / 2;
		if(x <= mid){
			if(!left) left = new segTree2d(l, mid);
			left->set(x, y, v);
		}
		if(x > mid){
			if(!right) right = new segTree2d(mid + 1, r);
			right->set(x, y, v);
		}
	}
 
	void add(int x, int X, int y, int Y, int v){
		push();
		if(x <= l && r <= X){
			lazy.push_back({v, {y, Y}});
			return;
		}
		
		int mid = (l + r) / 2;
		if(left && x <= mid) left->add(x, X, y, Y, v);
		if(right && X > mid) right->add(x, X, y, Y, v);
	}
 
	long qry(int x, int y){
		push();
		if(l == r) return (val ? val->qry(y) : -1);
		int mid = (l + r) / 2;
		if(left && x <= mid) return left->qry(x, y);
		if(right && x > mid) return right->qry(x, y);
		return -1;
	}
};

int n, m;
int a[maxn];
pii q[maxn];
segTree l(0, maxn), r(0, maxn);
segTree2d tre(0, maxn);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0, j = 0; i < n; i++){
		char c;
		cin >> c;
		a[i] = c - '0';
		if(a[i]){
			l.set(i, j);
			r.set(i, i);
			r.add(j, i - 1, 1);
		}else{
			l.set(i, -1);
			r.set(i, -1);
			j = i + 1;
		}
	}
	
	for(int i = 0; i < m; i++){
		string s;
		cin >> s;
		if(s[0] == 'q'){
			q[i].f = 1;
			cin >> q[i].s.f >> q[i].s.s;
			q[i].s.f--, q[i].s.s -= 2;
			tre.set(q[i].s.f, q[i].s.s, (r.qry(q[i].s.f) >= q[i].s.s));
		}else{
			q[i].f = 0;
			cin >> q[i].s.f;
			q[i].s.f--;
		}
	}
	
	for(int i = 0; i < m; i++){
		if(q[i].f){
			cout << (tre.qry(q[i].s.f, q[i].s.s) + i * (r.qry(q[i].s.f) >= q[i].s.s)) << endl;
		}else{
			if(a[q[i].s.f]){
				int lq = l.qry(q[i].s.f), rq = r.qry(q[i].s.f);
				r.add(lq, q[i].s.f - 1, q[i].s.f - rq - 1);
				l.add(q[i].s.f + 1, rq, q[i].s.f - lq + 1);
				tre.add(lq, q[i].s.f, q[i].s.f, rq, i);
				l.set(q[i].s.f, -1), r.set(q[i].s.f, -1);
			}else{
				int lq = (q[i].s.f && a[q[i].s.f - 1] ? l.qry(q[i].s.f - 1) : q[i].s.f);
				int rq = (q[i].s.f < n - 1 && a[q[i].s.f + 1] ? r.qry(q[i].s.f + 1) : q[i].s.f);
				r.add(lq, q[i].s.f - 1, rq - q[i].s.f + 1);
				l.add(q[i].s.f + 1, rq, lq - q[i].s.f - 1);
				tre.add(lq, q[i].s.f, q[i].s.f, rq, -i);
				l.set(q[i].s.f, lq), r.set(q[i].s.f, rq);
			}
			a[q[i].s.f] ^= 1;
		}
	}

	return 0;
}