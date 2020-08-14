/*
  For x coordinate you need to find the bounding points of vertical lines that cross through the points y's coordinate, and do the
equivalent to find bounding points for the y coordinate. If all lines spanned across the whole vertical range it would be easy, just
store the lines' x coordinates in a set and use lowerbound. We could then imagine storing a set for every vertical point, then the
we would still only have to query one set to find the bounding points, but inserting a line will take O(nlgn). To speed this up, we
can maintain a segment tree where each range has a set correspoinding to all x coordinates of lines that completely covers the range
of y coordinates corresponding to the range in the segment tree. We could then add new lines to the tree with range updates in O(lg^2)
time, and query the closest lines at a point by just querying each of the ranges the point falls inside of in O(lg^2) time, which is
fast enough for the problem..
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
pi operator+(pi x, pi y){
	return {max(x.f, y.f), min(x.s, y.s)};
}
 
const int inf = 0x3f3f3f3f;
 
struct segTree{
	int l, r;
	segTree *left, *right;
	set<int> s;
	
	segTree(int a, int b){
		l = a, r = b;
		s.insert(-inf);
		s.insert(inf);
		if(l != r){
			int mid = (l + r) / 2;
			left = new segTree(l, mid);
			right = new segTree(mid + 1, r);
		}
	}
	
	pi amt(int x){
		auto it = s.lower_bound(x);
		return {*it == x ? x :*prev(it), *it}; 
	}
	
	void add(int a, int b, int v){
		if(b < l || r < a) return;
		if(a <= l && r <= b){
			s.insert(v);
			return;
		}
		left->add(a, b, v);
		right->add(a, b, v);
	}
	
	pi qry(int x, int y){
		if(x < l || r < x) return {-inf, inf};
		if(l == r) return amt(y);
		return left->qry(x, y) + amt(y) + right->qry(x, y);
	}
};
 
const int mxn = 100000;
int n, m, q;
segTree tx(0, mxn), ty(0, mxn);
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	
	for(int i = 0; i < 2; i++){
		tx.add(0, m, i * n);
		ty.add(0, n, i * m);
	}
	
	while(q--){
		ll t, x, y, r1, r2;
		cin >> x >> y >> t;
		pi a = tx.qry(y, x);
		pi b = ty.qry(x, y);
		if(!~-t){
			r1 = (a.s - a.f) * (y - b.f);
			r2 = (a.s - a.f) * (b.s - y);
			ty.add(a.f, a.s, y);
		}else{
			r1 = (x - a.f) * (b.s - b.f);
			r2 = (a.s - x) * (b.s - b.f);
			tx.add(b.f, b.s, x);
		}
		if(r1 > r2) swap(r1, r2);
		cout << r1 << " " << r2 << endl;
	}
 
	return 0;
}
