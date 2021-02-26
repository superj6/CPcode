/*
	The most obvious thing that comes to mind is using a 2d segment tree, but you can't lazy propogate on 2d
segtrees. First consider how to solve the problem in 1 dimension with the restriction that you are not allowed to
lazily propogate a value down the tree. You can solve this by holding two values per node, one the maximum value
that will be located somewhere within the range, and the maximum value that will be held completely within the range.
The first value is updated for every node touched as you traverse the tree for the range update, and the second
value is updated on the which the traversal stops completely within the update range. 
	Now to query a range, realize as you traverse down the tree, every previous range update either stops at a
node above where the query range stops, or it stops somewhere within the current node subtree. For every update that
stopped before the query, you can update the query result value with the second value type, since the whole subtree
will be updated with that value including the part of the range you traverse within that subtree. Now when the query
traversal reaches a stopping node, you can update the result with the first value type of that node, since the query
will take the max of every value in that range so it doesn't matter that the update corresponding to it only took up
part of the range. You can see this takes into all previous updates while only updating values in place.
	To extend this to 2d, you can do the exact same thing, except the two values replaced with two segtrees that
are updated equivalently to the 1d case. You can see that when you traverse for both update and query ranges, each
segment tree hits O(lgn) nodes in that dimension, and the first dimension causes causes causes a traversal in each
second dimension segtree within each of the nodes the traversal hits, so we indeed get a O(lg^2n) time update and 
query just like in a point update 2d segtree. 
	You can see that I even coded it to extend to k dimensions using variadic templates, where the time becomes 
O(2^k * lg^kn) per update and query in k dimensions. However coding segtrees as structs took too much time naively
for the problem, so I had to make the segtree sparse, where it only allocates nodes as needed. Also, it is cool to
note the same technique can be extended to range addition updates with range sum queries, only slightly modifying
how to handle the two types of values.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

template<int... LR> struct segTred{
	int vl = 0;
	void add(int v){ vl = max(vl, v);}
	int qry(){ return vl;}
};

template<int L, int R, int... LR> struct segTred<L, R, LR...>{
	struct segTree{
		int l, r;
		segTree *tl, *tr;
		segTred<LR...> *vl1, *vl2;
		
		segTree(int l, int r) : l(l), r(r){
			tl = tr = 0, vl1 = vl2 = 0;
		}
		
		template<typename... AB> void add(int a, int b, AB... ab){
			if(b < l || r < a) return;
			if(!vl1) vl1 = new segTred<LR...>();
			vl1->add(ab...);
			if(a <= l && r <= b){
				if(!vl2) vl2 = new segTred<LR...>();
				return vl2->add(ab...);
			} 
			int mid = (l + r) / 2;
			if(a <= mid){
				if(!tl) tl = new segTree(l, mid);
				tl->add(a, b, ab...);
			}
			if(b > mid){
				if(!tr) tr = new segTree(mid + 1, r);
				tr->add(a, b, ab...);
			}
		}
		
		template<typename... AB> int qry(int a, int b, AB... ab){
			if(b < l || r < a) return 0;
			if(a <= l && r <= b) return vl1 ? vl1->qry(ab...) : 0;
			return max({
				vl2 ? vl2->qry(ab...) : 0, 
				tl ? tl->qry(a, b, ab...) : 0, 
				tr ? tr->qry(a, b, ab...) : 0
			});
		}
	} *vl = 0;
	
	template<typename... AB> void add(int a, int b, AB... ab){
		if(!vl) vl = new segTree(L, R);
		vl->add(a, b, ab...);
	}
	
	template<typename... AB> int qry(int a, int b, AB... ab){ 
		if(!vl) vl = new segTree(L, R);
		return vl->qry(a, b, ab...);
	}
};

const int mxn = 1000;
int n, m, q;
segTred<0, mxn, 0, mxn> tre;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	
	while(q--){
		int x, y, X, Y, z;
		cin >> X >> Y >> z >> x >> y;
		X += x - 1, Y += y - 1;
		tre.add(x, X, y, Y, tre.qry(x, X, y, Y) + z);
	}
	
	cout << tre.qry(0, n - 1, 0, m - 1) << endl;
	
	return 0;
}