#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
 
struct segTree{
	int l, r;
	segTree *left, *right;
	long val, lazy = 0, amt = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	long value(){
		int d = r - l + 1;
		return val + lazy * d + amt * d * (d - 1) / 2;
	}
	
	void push(){
		left->lazy += lazy;
		left->amt += amt;
		right->lazy += lazy + amt * ((r - l) / 2 + 1);
		right->amt += amt;
		lazy = 0;
		amt = 0;
	}
	
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lazy += v * (l - a + 1);
			amt += v;
			return;
		}
		
		push();
		
		left->add(a, b, v);
		right->add(a, b, v);
		val = left->value() + right->value();
	}
	
	long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return value();
		
		push();
		val = left->value() + right->value();
		
		return left->qry(a, b) + right->qry(a, b);
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
		int t, a, b;
		cin >> t >> a >> b;
		
		if(t == 1){
			tre.add(a, b, 1);
		}else{
			cout << tre.qry(a, b) << endl;
		}
	}
 
	return 0;
}