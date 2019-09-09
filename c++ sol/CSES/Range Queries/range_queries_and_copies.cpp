#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
#define endl '\n'
 
struct segTree{
	int l, r;
	segTree *left, *right;
	long val;
	bool chg = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
		
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	segTree(segTree *cpy){
		l = cpy->l;
		r = cpy->r;
		left = cpy->left;
		right = cpy->right;
		val = cpy->val;

		if(l != r){
			cpy->left->chg = 1;
			cpy->right->chg = 1;
		}
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r){
			val = v;
			return;
		}
		
		if(left->chg) left = new segTree(left);
		if(right->chg) right = new segTree(right);
		
		left->add(x, v);
		right->add(x, v);
		val = left->val + right->val;
	}
	
	long qry(int a, int b){
		if(r < a || b < l) return 0;
		if(a <= l && r <= b) return val;
		
		return left->qry(a, b) + right->qry(a, b);
	}
};
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	vector<segTree*> tre(1, new segTree(1, n));
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		tre[0]->add(i, x);
	}
	
	for(int i = 0; i < q; i++){
		int t, k;
		cin >> t >> k;
		k--;
		
		if(t == 1){
			int a, x;
			cin >> a >> x;
			tre[k]->add(a, x);
		}else if(t == 2){
			int a, b;
			cin >> a >> b;
			cout << tre[k]->qry(a, b) << endl;
		}else{
			tre.push_back(new segTree(tre[k]));
		}
	}
 
	return 0;
}
