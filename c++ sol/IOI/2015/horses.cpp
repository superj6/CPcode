#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <string.h>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
//solution
const int mod = 1000000007;
const int k = 2;
const int rv[k] = {1, 0};
function<int(int, int)> f[k] = {
	[](int x, int y){ return (ll)x * y % mod;},
	[](int x, int y){ return max(x, y);}
};
 
struct segTree{
	int l, r;
	segTree *left, *right;
	int val[k];
	
	segTree(int a, int b){
		l = a, r = b;
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
		memcpy(val, rv, sizeof(val));
	}
	
	void add(int x, int v, int t){
		if(x < l || r < x) return;
		if(l == r){
			val[t] = v;
			return;
		}
		left->add(x, v, t);
		right->add(x, v, t);
		val[t] = f[t](left->val[t], right->val[t]);
	}
	
	int qry(int a, int b, int t){
		if(b < l || r < a) return rv[t];
		if(a <= l && r <= b) return val[t];
		return f[t](left->qry(a, b, t), right->qry(a, b, t));
	}
};
 
const int mxn = 500000;
int n;
int *x, *y;
set<int, greater<int>> s;
segTree tre(0, mxn);
 
void addx(int a, int b){
	if(a){
		if(~-x[a]) s.erase(a);
		if(~-(x[a] = b)) s.insert(a);
	}else{
		x[a] = b;
	}
	tre.add(a, b, 0);
}
 
void addy(int a, int b){
	y[a] = b;
	tre.add(a, b, 1);
}
 
int sol(){
	auto it = ++s.begin();
	__int128 cur, b, ret;
	for(cur = 1; it != s.end() && cur < mod; it++) cur *= x[*it];
	if(it == s.end()) it--;
	for(cur = 1, b = *it, ret = 0; it != s.begin(); it--){
		cur *= x[*it];
		ret = max(ret, cur * tre.qry(*it, *prev(it) - 1, 1));
	}
	return ret % mod * tre.qry(0, b - 1, 0) % mod;
}
//end solution
 
//interaction
int init(int N, int *X, int *Y){
	n = N, x = X, y = Y;
	s.insert(0), s.insert(n);
	for(int i = 0; i < n; i++){
		addx(i, x[i]);
		addy(i, y[i]);
	}
	return sol();
}
 
int updateX(int a, int b){
	addx(a, b);
	return sol();
}
 
int updateY(int a, int b){
	addy(a, b);
	return sol();
}
//end interaction

//test
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	int n, q;
	
	cin >> n;
	int x[n], y[n];
	
	for(int i = 0; i < n; i++) cin >> x[i];
	for(int i = 0; i < n; i++) cin >> y[i];
	
	cout << init(n, x, y) << endl;
	
	cin >> q;
	while(q--){
		int t, a, b;
		cin >> t >> a >> b;
		cout << (t == 1 ? updateX(a, b) : updateY(a, b)) << endl;
	}
 
	return 0;
}
//end test