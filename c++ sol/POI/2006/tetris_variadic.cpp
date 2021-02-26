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
			vl1 = new segTred<LR...>(), vl2 = new segTred<LR...>();
			if(l != r){
				int mid = (l + r) / 2;
				tl = new segTree(l, mid);
				tr = new segTree(mid + 1, r);
			}
		}
		
		template<typename... AB> void add(int a, int b, AB... ab){
			if(b < l || r < a) return;
			vl1->add(ab...);
			if(a <= l && r <= b) return vl2->add(ab...);
			tl->add(a, b, ab...), tr->add(a, b, ab...);
		}
		
		template<typename... AB> int qry(int a, int b, AB... ab){
			if(b < l || r < a) return 0;
			if(a <= l && r <= b) return vl1->qry(ab...);
			return max({vl2->qry(ab...), tl->qry(a, b, ab...), tr->qry(a, b, ab...)});
		}
	} *vl;
	
	segTred(){ vl = new segTree(L, R);}
	
	template<typename... AB> void add(int a, int b, AB... ab){
		vl->add(a, b, ab...);
	}
	
	template<typename... AB> int qry(int a, int b, AB... ab){ 
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