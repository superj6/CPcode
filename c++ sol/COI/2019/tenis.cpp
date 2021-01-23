#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000, k = 3;
int n, q;
int a[mxn][k], f[mxn];

int ff(int x){
	return *max_element(a[x], a[x] + k);
}

struct segTree{
	int l, r;
	segTree *tl, *tr;
	int vl, ss;
	
	segTree(int l, int r) : l(l), r(r){
		if(l != r){
			int mid = (l + r) / 2;
			tl = new segTree(l, mid);
			tr = new segTree(mid + 1, r);
			pul();
		}else{
			vl = ss = f[l] - 1;
		}
	}
	
	void pul(){
		vl = max(tl->vl, tl->ss + tr->vl);
		ss = tl->ss + tr->ss;
	}
	
	void add(int x, int v){
		if(x < l || r < x) return;
		if(l == r) return (void)(vl += v, ss += v);
		tl->add(x, v), tr->add(x, v);
		pul();
	}
	
	int qry(int x = 0){
		return l == r ? l : !(x + tl->vl) ? tl->qry(x) : tr->qry(x + tl->ss);
	}
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int j = 0; j < k; j++)
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		a[--x][j] = i;
	}
	
	for(int i = 0; i < n; i++) f[ff(i)]++;
	
	segTree tre(0, n - 1);
	while(q--){
		int t;
		cin >> t;
		if(t & 1){
			int x;
			cin >> x;
			x--;
			cout << (ff(x) <= tre.qry() ? "DA" : "NE") << endl;
		}else{
			int x, y, z;
			cin >> z >> x >> y;
			x--, y--, z--;
			tre.add(ff(x), -1), tre.add(ff(y), -1);
			swap(a[x][z], a[y][z]);
			tre.add(ff(x), 1), tre.add(ff(y), 1);
		}
	}
	
	return 0;
}