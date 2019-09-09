#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
 
struct segTree{
	int l, r;
	segTree *left, *right;
	long val = 0, lazy = 0, lazy2 = 0;
	
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
		if(lazy2){
			val = lazy2 * (r - l + 1); 
		} 
		return val + lazy * (r - l + 1);
	}
	
	void push(){
		if(lazy2){
			left->lazy = 0;
			right->lazy = 0;
			lazy = 0;
			
			left->lazy2 = lazy2;
			right->lazy2 = lazy2;
			lazy2 = 0;
		}else{
			if(left->lazy2) left->lazy2 += lazy;
			else left->lazy += lazy;
			if(right->lazy2) right->lazy2 += lazy;
			else right->lazy += lazy;
			lazy = 0;
		}
	}
	
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			if(l != r){
				push();
				val = left->amt() + right->amt();
			}else if(lazy2){
				val = lazy2;
				lazy2 = 0;
			}
			lazy += v;
			return;
		}
		
		push();
		
		left->add(a, b, v);
		right->add(a, b, v);
		val = left->amt() + right->amt();
	}
	
	void add2(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lazy = 0;
			lazy2 = v;
			return;
		}
		
		push();
		
		left->add2(a, b, v);
		right->add2(a, b, v);
		val = left->amt() + right->amt();
	}
	
	long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return amt();
		
		push();
		
		long ret = left->qry(a, b) + right->qry(a, b);
		val = left->amt() + right->amt();
		return ret;
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
		
		if(t < 3){
			int x;
			cin >> x;
			if(t == 1) tre.add(a, b, x);
			else tre.add2(a, b, x);
		}else{
			cout << tre.qry(a, b) << endl;
		}
	}
 
	return 0;
}