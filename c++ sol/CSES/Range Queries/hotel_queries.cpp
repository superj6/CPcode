#include <iostream>
#include <cstdio>
#include <algorithm>
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
		val = max(left->val, right->val);
	}
	
	int qry(int v){
		if(v > val) return 0;
		if(l == r){
			val -= v;
			return l + 1;
		}
		
		int ret;
		if(left->val >= v) ret = left->qry(v);
		else ret = right->qry(v);
		
		val = max(left->val, right->val);
		return ret;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	segTree tre(0, n - 1);
	for(int i = 0; i < n; i++){
		int h;
		cin >> h;
		tre.add(i, h);
	}
	
	for(int i = 0; i < m; i++){
		int x;
		cin >> x;
		cout << tre.qry(x);
		if(i == m - 1) cout << endl;
		else cout << " ";
	}
	
	return 0;
}