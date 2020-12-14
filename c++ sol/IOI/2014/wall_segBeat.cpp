#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;

struct segTree{
	int l, r;
	segTree *tl, *tr;
	int mx1, mx2, mxl, mn1, mn2, mnl;
	
	segTree(int a, int b){
		l = a, r = b;
		mx1 = mn1 = 0, mx2 = -inf, mn2 = inf, mxl = mnl = -1;
		if(l != r){
			int mid = (l + r) / 2;
			tl = new segTree(l, mid);
			tr = new segTree(mid + 1, r);
		}
	}
	
	void upx(int x){
		if(x <= mn1) return;
		if(mx1 == mn1) mx1 = x;
		if(mx2 == mn1) mx2 = x;
		mn1 = mxl = x;
		if(l != r && ~mnl) tl->upn(mnl), tr->upn(mnl);
		mnl = -1;
	}
	
	void upn(int x){
		if(x >= mx1) return;
		if(mn1 == mx1) mn1 = x;
		if(mn2 == mx1) mn2 = x;
		mx1 = mnl = x;
	}
	
	void pull(){
		mx1 = max(tl->mx1, tr->mx1);
		mx2 = max(tl->mx2, tr->mx2);
		if(tl->mx1 != mx1) mx2 = max(mx2, tl->mx1);
		if(tr->mx1 != mx1) mx2 = max(mx2, tr->mx1);
		
		mn1 = min(tl->mn1, tr->mn1);
		mn2 = min(tl->mn2, tr->mn2);
		if(tl->mn1 != mn1) mn2 = min(mn2, tl->mn1);
		if(tr->mn1 != mn1) mn2 = min(mn2, tr->mn1);
	}
	
	void push(){
		if(~mxl) tl->upx(mxl), tr->upx(mxl);
		if(~mnl) tl->upn(mnl), tr->upn(mnl);
		mxl = mnl = -1;
	}
	
	void adx(int a, int b, int v){
		if(b < l || r < a || v <= mn1) return;
		if(a <= l && r <= b && v < mn2) return upx(v);
		push();
		tl->adx(a, b, v), tr->adx(a, b, v);
		pull();
	}
	
	void adn(int a, int b, int v){
		if(b < l || r < a || v >= mx1) return;
		if(a <= l && r <= b && v > mx2) return upn(v);
		push();
		tl->adn(a, b, v), tr->adn(a, b, v);
		pull();
	}
	
	void sol(int ans[]){
		if(l == r) return (void)(ans[l] = mn1);
		push();
		tl->sol(ans), tr->sol(ans);
		pull();
	}
};

void buildWall(int n, int q, int t[], int l[], int r[], int h[], int ans[]){
	segTree tre(0, n - 1);
	
	for(int i = 0; i < q; i++){
		if(t[i] & 1) tre.adx(l[i], r[i], h[i]);
		else tre.adn(l[i], r[i], h[i]);
	}
	
	tre.sol(ans);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	int t[q], l[q], r[q], h[q];
	int ans[n];
	
	for(int i = 0; i < q; i++) cin >> t[i] >> l[i] >> r[i] >> h[i];
	
	buildWall(n, q, t, l, r, h, ans);
	
	cout << ans[0];
	for(int i = 1; i < n; i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}