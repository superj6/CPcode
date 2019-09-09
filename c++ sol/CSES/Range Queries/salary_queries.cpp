#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
 
struct segTree{
	int l, r;
	segTree *left = NULL, *right = NULL;
	long val = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r){
			val += v;
			return;
		}
		
		int mid = (l + r) / 2;
		if(x <= mid){
			if(!left) left = new segTree(l, mid);
			left->add(x, v);
		}else{
			if(!right) right = new segTree(mid + 1, r);
			right->add(x, v);
		}
		
		val = (left ? left->val : 0) + (right ? right->val : 0);
	}
	
	long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return val;
		
		return (left ? left->qry(a, b) : 0) + (right ? right->qry(a, b) : 0);
	}
};
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	int a[n];
	segTree tre(1, 1 << 30);
	for(int i = 0; i < n; i++){
		cin >> a[i];
		tre.add(a[i], 1);
	}
	
	for(int i = 0; i < q; i++){
		char t;
		cin >> t;
		
		if(t == '!'){
			int k, x;
			cin >> k >> x;
			k--;
			tre.add(a[k], -1);
			a[k] = x;
			tre.add(a[k], 1);
		}else{
			int a, b;
			cin >> a >> b;
			cout << tre.qry(a, b) << endl;;
		}
	}
 
	return 0;
}