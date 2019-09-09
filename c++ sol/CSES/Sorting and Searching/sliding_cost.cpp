#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

struct segTree{
	int l, r;
	segTree *left = NULL, *right = NULL;
	int sum = 0;
	long sum2 = 0;
	
	segTree(int a, int b){
		l = a;
		r = b;
	}
	
	void add(int i, int x){
		if(l == r){
			sum += x;
			sum2 += l * x;
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
		sum2 = (left ? left->sum2 : 0) + (right ? right->sum2 : 0);
	}
	
	pair<int, int> qry(int val, int cur = 0){
		if(l == r) return make_pair(l, cur + sum);
		
		if(cur + (left ? left->sum : 0) >= val){
			return left->qry(val, cur);
		}else{
			return right->qry(val, cur + (left ? left->sum : 0));
		}
	}
	
	long qry2(int a, int b){
		if(a > r || b < l) return 0;
		if(l >= a && r <= b){
			return sum2;
		}
		
		return (left ? left->qry2(a, b) : 0) + (right ? right->qry2(a, b) : 0);
	}
};

int n, k;
segTree *tre = new segTree(1, 1e9);

long chg(){
	pair<int, int> cur = tre->qry((k + 1) / 2);
	
	long below = (long)cur.first * cur.second - tre->qry2(1, cur.first);
	long above = tre->qry2(cur.first + 1, 1e9) - (long)cur.first * (k - cur.second);
	
	return below + above;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	int a[n];
	
	for(int i = 0; i < k; i++){
		cin >> a[i];
		
		tre->add(a[i], 1);
	}
	
	cout << chg();
	
	for(int i = k; i < n; i++){
		cin >> a[i];
		tre->add(a[i - k], -1);
		tre->add(a[i], 1);
		
		cout << " " << chg();
	}
	
	cout << endl;

	return 0;
}