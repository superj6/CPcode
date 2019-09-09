#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
 
struct segTree{
	int l, r;
	segTree *left, *right;
	int val, ind;
	
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
			ind = 1;
			return;
		}
		
		left->add(x, v);
		right->add(x, v);
		ind = left->ind + right->ind;
	}
	
	int qry(int v){
		if(v > ind) return 0;
		if(l == r){
			ind = 0;
			return val;
		}
		
		int ret;
		if(left->ind >= v) ret = left->qry(v);
		else ret = right->qry(v - left->ind);
		
		ind = left->ind + right->ind;
		return ret;
	}
};
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n;
	cin >> n;
	
	segTree tre(0, n - 1);
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		tre.add(i, x);
	}
	
	for(int i = 0; i < n; i++){
		int p;
		cin >> p;
		cout << tre.qry(p);
		if(i == n - 1) cout << endl;
		else cout << " ";
	}
	
	return 0;
}