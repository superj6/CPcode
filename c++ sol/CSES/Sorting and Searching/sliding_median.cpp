#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left = NULL, *right = NULL;
	int sum = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
	}
	
	void add(int i, int x){
		if(l == r){
			sum += x;
			return;
		}
		
		int mid = l + (r - l) / 2;
		
		if(i <= mid){
			if(!left) left = new segTree(l, mid);
			left->add(i, x);
		}else{
			if(!right) right = new segTree(mid + 1, r);
			right->add(i, x);
		}
		
		sum = (left ? left->sum : 0) + (right ? right->sum : 0);
	}
	
	int qry(int val, int cur = 0){
		if(l == r) return l;
		
		if(cur + (left ? left->sum : 0) >= val){
			return left->qry(val, cur);
		}else{
			return right->qry(val, cur + (left ? left->sum : 0));
		}
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	int a[n];
	segTree *tre = new segTree(1, 1e9);
	
	for(int i = 0; i < k; i++){
		cin >> a[i];
		
		tre->add(a[i], 1);
	}
	
	cout << tre->qry((k + 1) / 2);
	
	for(int i = k; i < n; i++){
		cin >> a[i];
		tre->add(a[i - k], -1);
		tre->add(a[i], 1);
		
		cout << " " << tre->qry((k + 1) / 2);
	}
	
	cout << endl;

	return 0;
}