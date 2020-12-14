#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

struct segTree{
	int l, r;
	segTree *left, *right;
	int val = 0, lzy = 0;
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	int amt(){
		return val + lzy;
	}
	
	void push(){
		left->lzy += lzy;
		right->lzy += lzy;
		lzy = 0;
	}
	
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			lzy += v;
			return;
		}
		push();
		left->add(a, b, v);
		right->add(a, b, v);
		val = max(left->amt(), right->amt());
	}
};

const int mxn = 200000;
int n, m, k;
pii a[mxn];
int it[mxn];
segTree tre(0, mxn);

int id(int x){
	return lower_bound(it, it + k, x) - it;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int l, x, y, z, d, dd;
		cin >> l >> x;
		l /= 2, x *= 2, d = 0;
		for(int j = 0; j < l; j++, x = z, d = dd){
			cin >> y; if(j < l - 1) cin >> z, z *= 2; else z = a[m - j].s.f;
			if(d == (dd = abs(z - x) / (z - x))) it[k++] = x, x += d;
			a[m++] = {y, {it[k++] = x, z}};
		}
		z = a[m - l].s.s;
		if(d == abs(z - x) / (z - x)) it[k++] = (a[m - l].s.f += d);
	}
	
	sort(a, a + m);
	sort(it, it + k);
	k = unique(it, it + k) - it;
	
	int ret = 0;
	for(int i = 0; i < m; i++){
		int x = a[i].s.f, y = a[i].s.s;
		if(x > y) swap(x, y);
		tre.add(id(x), id(y), 2 * (x == a[i].s.f) - 1);
		ret = max(ret, tre.amt());
	}
	
	cout << ret << endl;

	return 0;
}