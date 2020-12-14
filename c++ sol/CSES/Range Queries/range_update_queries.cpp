#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	long val = 0, lazy = 0;
 
	segTree(int a, int b){
		l = a;
		r = b;
 
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
 
	long amt(){
		return val + lazy;
	}
 
	void push(){
		left->lazy += lazy;
		right->lazy += lazy;
		lazy = 0;
	}
 
	void pull(){
		val = left->amt() + right->amt();
	}
 
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lazy += v;
			return;
		}
 
		push();
 
		left->add(a, b, v);
		right->add(a, b, v);
		pull();
	}
 
	long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return amt();
 
		push();
		pull();
 
		return max(left->qry(a, b), right->qry(a, b));
	}
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	segTree tre(1, n);
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		tre.add(i, i, x);
	}
	
	for(int i = 0; i < q; i++){
		int t;
		cin >> t;
		
		if(t == 1){
			int a, b, u;
			cin >> a >> b >> u;
			tre.add(a, b, u);
		}else{
			int k;
			cin >> k;
			cout << tre.qry(k, k) << endl;;
		}
	}

	return 0;
}