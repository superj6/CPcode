#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int k = 2;
struct segTree{
	int l, r;
	segTree *tl, *tr;
	int vl[1 << k], lz[k];
	
	segTree(int l, int r) : l(l), r(r){
		memset(vl, 0, sizeof(vl));
		memset(lz, 0, sizeof(lz));
		vl[0] = r - l + 1;
		if(l != r){
			int mid = (l + r) / 2;
			tl = new segTree(l, mid);
			tr = new segTree(mid + 1, r);
		}
	}
	
	void upd(int x, int v){
		lz[x] += v;
		for(int i = 0; i < (1 << k); i++){
			if((i >> x) & 1) vl[i] += v * vl[i ^ (1 << x)];
		}
	}
	
	void add(int a, int b, int x, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b) return upd(x, v);
		for(int i = 0; i < k; i++){
			if(lz[i]) tl->upd(i, lz[i]), tr->upd(i, lz[i]), lz[i] = 0;
		}
		tl->add(a, b, x, v), tr->add(a, b, x, v);
		for(int i = 0; i < (1 << k); i++){
			vl[i] = tl->vl[i] + tr->vl[i];
		}
	}
	
	int qry(int a, int b){
		if(b < l || r < a) return 0;
		if(a <= l && r <= b) return vl[(1 << k) - 1];
		return tl->qry(a, b) + tr->qry(a, b);
	}
};

const int mxn = 200000;
int n;
int p[mxn], pp[mxn]; //two most recent previous positions
segTree tre(0, mxn); //holds useable left points and # mid points per left point

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	memset(p, -1, sizeof(p));
	memset(pp, -1, sizeof(pp));
	
	ll ret = 0;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		x--;
		
		//remove previous from left mid pairs
		tre.add(p[x], p[x], 0, -1);
		tre.add(pp[x] + 1, p[x] - 1, 1, -1);
		
		//add number of triples with current right point to total
		ret += tre.qry(p[x] + 1, i - 1);
		
		//update new left mid pairs
		tre.add(i, i, 0, 1);
		tre.add(p[x] + 1, i - 1, 1, 1);
		
		//update previous for color
		pp[x] = p[x], p[x] = i;
	}
	
	cout << ret << endl;
	
	return 0;
}