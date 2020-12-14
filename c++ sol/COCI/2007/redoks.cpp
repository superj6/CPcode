#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int k = 10;
typedef array<int, k> T;
T operator+(T a, T b){
	T ret;
	for(int i = 0; i < k; i++) ret[i] = a[i] + b[i];
	return ret;
}

struct segTree{
	int l, r;
	segTree *left, *right;
	T val;
	int lzy = 0;
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
		val[0] = 1;
	}
	
	void upd(int x){
		if(!x) return;
		T a = val;
		lzy = (lzy + x) % 10;
		for(int i = 0; i < k; i++){
			val[i] = a[(i - x + k) % k];
		}
	}
	
	void push(){
		left->upd(lzy), right->upd(lzy);
		lzy = 0;
	}
	
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			upd(v);
			return;
		}
		push();
		left->add(a, b, v), right->add(a, b, v);
		val = left->val + right->val;
	}
	
	T qry(int a, int b){
		if(b < l || r < a) return T();
		if(a <= l && r <= b) return val;
		push();
		return left->qry(a, b) + right->qry(a, b);
	}
};

const int mxn = 250000;
int n, q;
T a;
segTree tre(1, mxn);

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++){
		char c;
		cin >> c;
		tre.add(i, i, c - '0');
	}
	
	while(q--){
		int x, y;
		cin >> x >> y;
		a = tre.qry(x, y);
		ll ret = 0;
		for(int i = 0; i < k; i++) ret += a[i] * i;
		cout << ret << endl;
		tre.add(x, y, 1);
	}

	return 0;
}