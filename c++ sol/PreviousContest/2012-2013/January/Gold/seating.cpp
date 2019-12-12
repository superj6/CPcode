#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	int vl, vm, vr, lazy;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		vl = vm = vr = r - l + 1;
		lazy = -1;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void set(){
		if(lazy != -1){
			vl = vm = vr = lazy * (r - l + 1);
		}
	}
	
	void push(){
		if(lazy != -1){
			if(l != r){
				left->lazy = lazy;
				right->lazy = lazy;
			}
			set();
			lazy = -1;
		}
	}
	
	void pull(){
		if(l == r) return;
		left->set();
		right->set();
		
		int mid = (l + r) / 2;
		if(left->vl == mid - l + 1) vl = left->vl + right->vl;
		else vl = left->vl;
		if(right->vr == r - mid) vr = left->vr + right->vr;
		else vr = right->vr;
		vm = max(max(max(vl, vr), max(left->vm, right->vm)), left->vr + right->vl);
	}
	
	void add(int a, int b, int x){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lazy = x;
			set();
			return;
		}
		
		push();
		left->add(a, b, x);
		right->add(a, b, x);
		pull();
	}
	
	int qry(int x){
		if(vm < x) return -1;
		if(l == r) return l;
		
		push();
		pull();
		
		if(left->vm >= x) return left->qry(x);
		else if(left->vr && left->vr + right->vl >= x) return (l + r) / 2 - left->vr + 1;
		else return right->qry(x);
	}
	
	int debug(int a, int b){
	    if(b < l || r < a) return -1;
	    if(a <= l && r <= b){
	        return vm;
	    }
	    
	    push();
	    pull();
	    
	    return max(left->debug(a, b), right->debug(a, b));
	}
};

int main() {
	freopen("seating.in", "r", stdin);
	freopen("seating.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	int ret = 0;
	segTree tre(1, n);
	for(int i = 0; i < m; i++){
		char t;
		cin >> t;
		
		if(t == 'A'){
			int p;
			cin >> p;
			
			int x = tre.qry(p);
			if(x == -1){
				ret++;
			}else{
				tre.add(x, x + p - 1, 0);
			}
		}else{
			int l, r;
			cin >> l >> r;
			tre.add(l, r, 1);
		}
	}
	
	cout << ret << endl;
	
	return 0;
}