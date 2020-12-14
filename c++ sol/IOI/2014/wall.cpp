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
	int mn = 0, mx = inf;
	
	segTree(int a, int b){
		l = a, r = b;
		mn = 0, mx = inf;
		if(l != r){
			int mid = (l + r) / 2;
			tl = new segTree(l, mid);
			tr = new segTree(mid + 1, r);
		}
	}
	
	void upd(int vl, int vr){
		mn = min(max(mn, vl), vr);
		mx = min(max(mx, vl), vr);
	}
	
	void psh(){
		tl->upd(mn, mx), tr->upd(mn, mx);
		mn = 0, mx = inf;
	}
	
	void add(int a, int b, int vl, int vr){
		if(b < l || r < a) return;
		if(a <= l && r <= b) return upd(vl, vr);
		psh();
		tl->add(a, b, vl, vr), tr->add(a, b, vl, vr);
	}
	
	void sol(int ans[]){
		if(l == r) return (void)(ans[l] = mn);
		psh();
		tl->sol(ans), tr->sol(ans);
	}
};

void buildWall(int n, int q, int t[], int l[], int r[], int h[], int ans[]){
	segTree tre(0, n - 1);
	
	for(int i = 0; i < q; i++){
		if(t[i] & 1) tre.add(l[i], r[i], h[i], inf);
		else tre.add(l[i], r[i], 0, h[i]);
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