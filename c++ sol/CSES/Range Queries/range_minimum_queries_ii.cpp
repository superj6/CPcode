#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	int val;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r){
			val = v;
			return;
		}
		
		left->add(x, v);
		right->add(x, v);
		val = min(left->val, right->val);
	}
	
	int qry(int a, int b){
		if(r < a || b < l) return 1000000007;
		if(a <= l && r <= b) return val;
		
		return min(left->qry(a, b), right->qry(a, b));
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
		tre.add(i, x);
	}
	
	for(int i = 0; i < q; i++){
		int t;
		cin >> t;
		
		if(t == 1){
			int k, x;
			cin >> k >> x;
			tre.add(k, x);
		}else{
			int a, b;
			cin >> a >> b;
			cout << tre.qry(a, b) << endl;
		}
	}

	return 0;
}