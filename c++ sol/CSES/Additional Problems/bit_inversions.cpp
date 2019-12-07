#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

struct segTree{
	int l, r;
	segTree *left, *right;
	int vl, vm, vr, lazy;
 
	segTree(int a, int b){
		l = a;
		r = b;
 
		vl = vm = vr = r - l + 1;
 
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
 
	void pull(){
		int mid = (l + r) / 2;
		if(left->vl == mid - l + 1) vl = left->vl + right->vl;
		else vl = left->vl;
		if(right->vr == r - mid) vr = left->vr + right->vr;
		else vr = right->vr;
		vm = max(max(max(vl, vr), max(left->vm, right->vm)), left->vr + right->vl);
	}
 
	void swap(int x){
		if(x < l || r < x) return;
		if(x <= l && r <= x){
			vl ^= 1, vm ^= 1, vr ^= 1;
			return;
		}
 
		left->swap(x);
		right->swap(x);
		pull();
	}
};

int n, m;
string s;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s >> m;
	n = s.size();
	
	segTree t0(1, n), t1(1, n);
	for(int i = 0; i < n; i++){
		if(s[i] == '0'){
			t1.swap(i + 1);
		}else{
			t0.swap(i + 1);
		}
	}
	
	while(m--){
		int x;
		cin >> x;
		
		t0.swap(x);
		t1.swap(x);
		
		cout << max(t0.vm, t1.vm);
		if(m) cout << " ";
		else cout << endl;
	}

	return 0;
}