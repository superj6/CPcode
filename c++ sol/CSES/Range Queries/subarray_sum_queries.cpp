#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left, *right;
	long sum, pre, suf, maxv;
	
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
			sum = v;
			pre = suf = maxv = max(v, 0);
			return;
		}
		
		left->add(x, v);
		right->add(x, v);
		
		sum = left->sum + right->sum;
		pre = max(left->pre, left->sum + right->pre);
		suf = max(right->suf, left->suf + right->sum);
		maxv = max(max(left->maxv, right->maxv), left->suf + right->pre);
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	segTree tre(1, n);
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		tre.add(i, x);
	}
	
	for(int i = 0; i < m; i++){
		int k, x;
		cin >> k >> x;
		tre.add(k, x);
		cout << tre.maxv << endl;
	}

	return 0;
}