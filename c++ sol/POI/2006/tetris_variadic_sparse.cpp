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