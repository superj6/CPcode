#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

struct segTree{
	int l, r;
	segTree *tl, *tr;
	int vl1, vl2;
	
	segTree(int l, int r) : l(l), r(r){
		vl1 = vl2 = 0;
		if(l != r){
			int mid = (l + r) / 2;
			tl = new segTree(l, mid);
			tr = new segTree(mid + 1, r);
		}
	}
	
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		vl1 = max(vl1, v);
		if(a <= l && r <= b) return (void)(vl2 = max(vl2, v));
		tl->add(a, b, v), tr->add(a, b, v);
	}
	
	int qry(int a, int b){
		if(b < l || r < a) return 0;
		if(a <= l && r <= b) return vl1;
		return max({vl2, tl->qry(a, b), tr->qry(a, b)});
	}
};

struct segTre2{
	int l, r;
	segTre2 *tl, *tr;
	segTree *vl1, *vl2;
	
	segTre2(int lx, int rx, int ly, int ry) : l(lx), r(rx){
		vl1 = new segTree(ly, ry), vl2 = new segTree(ly, ry);
		if(l != r){
			int mid = (l + r) / 2;
			tl = new segTre2(l, mid, ly, ry);
			tr = new segTre2(mid + 1, r, ly, ry);
		}
	}
	
	void add(int ax, int bx, int ay, int by, int v){
		if(bx < l || r < ax) return;
		vl1->add(ay, by, v);
		if(ax <= l && r <= bx) return vl2->add(ay, by, v);
		tl->add(ax, bx, ay, by, v), tr->add(ax, bx, ay, by, v);
	}
	
	int qry(int ax, int bx, int ay, int by){
		if(bx < l || r < ax) return 0;
		if(ax <= l && r <= bx) return vl1->qry(ay, by);
		return max({vl2->qry(ay, by), 
			tl->qry(ax, bx, ay, by), tr->qry(ax, bx, ay, by)});
	}
};

int n, m, q;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	
	segTre2 tre(0, n - 1, 0, m - 1);
	while(q--){
		int x, y, X, Y, z;
		cin >> X >> Y >> z >> x >> y;
		X += x - 1, Y += y - 1;
		tre.add(x, X, y, Y, tre.qry(x, X, y, Y) + z);
	}
	
	cout << tre.qry(0, n - 1, 0, m - 1) << endl;
	
	return 0;
}