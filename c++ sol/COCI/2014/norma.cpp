#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000000;
const int k = 3;

struct segTree{
	int l, r;
	segTree *tl, *tr;
	int vl[1 << k], lz[k];
	
	segTree(int l, int r) : l(l), r(r){
		memset(vl, 0, sizeof(vl));
		memset(lz, 0, sizeof(lz));
		vl[0] = r - l + 1;
		tl = tr = 0;
	}
	
	void upd(int x, int v){
		(lz[x] = !x * lz[x] + v) %= mod;
		for(int i = 0; i < (1 << k); i++){
			if((i >> x) & 1) (vl[i] = !x * vl[i] + (ll)v * vl[i ^ (1 << x)] % mod) %= mod;
		}
	}
	
	void add(int a, int b, int x, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b) return upd(x, v);
		int mid = (l + r) / 2;
		if(!tl) tl = new segTree(l, mid);
		if(!tr) tr = new segTree(mid + 1, r);
		for(int i = 0; i < k; i++){
			if(lz[i]) tl->upd(i, lz[i]), tr->upd(i, lz[i]), lz[i] = 0;
		}
		tl->add(a, b, x, v), tr->add(a, b, x, v);
		for(int i = 0; i < (1 << k); i++){
			vl[i] = (tl->vl[i] + tr->vl[i]) % mod;
		}
	}
};

const int mxn = 500001;
int n;
int a[mxn];
stack<int> s1, s2;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	ll ret = 0;
	segTree tre(1, n);
	s1.push(0), s2.push(0);
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		tre.add(1, i, 0, 1);
		
		while(s1.top() && a[i] >= a[s1.top()]) s1.pop();
		tre.add(s1.top() + 1, i, 1, a[i]);
		s1.push(i);
		
		while(s2.top() && a[i] <= a[s2.top()]) s2.pop();
		tre.add(s2.top() + 1, i, 2, a[i]);
		s2.push(i);
		
		(ret += tre.vl[(1 << k) - 1]) %= mod;
	}
	
	cout << ret << endl;
	
	return 0;
}