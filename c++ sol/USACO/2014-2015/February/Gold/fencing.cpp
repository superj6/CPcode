#include <iostream>
#include <cstdio>
#include <algorithm>
#include <complex>
#include <vector>
using namespace std;
#define endl '\n'

typedef long long num;
typedef complex<num> point;
typedef vector<point> poly;

num cp(point a, point b, point c = point(0, 0)){
	return imag(conj(a - c) * (b - c));
}

bool ccw(point a, point b, point c){
	return 0 < cp(a, b, c);
}

bool ccweq(point a, point b, point c){
	return 0 <= cp(a, b, c);
}

num dot(point a, point b, point c = point(0, 0)){
	return real(conj(a - c) * (b - c));
}

point pivot;
bool pointCmp(point a, point b){
	return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
}

bool angleCmp(point a, point b){
	num c = cp(pivot, a, b);
	return c == 0 && dot(a, a, pivot) < dot(b, b, pivot) || 0 < c;
}

void unwind(poly& p, point a){
	int sz = p.size();
	while(sz > 1 && ccweq(a, p[sz - 1], p[sz - 2])) sz--;
	p.resize(sz);
}

poly hull(poly p){
	swap(p[0], *min_element(p.begin(), p.end(), pointCmp));
	pivot = p[0];
	sort(p.begin() + 1, p.end(), angleCmp);
	
	poly ret(1, pivot);
	for(int i = 1; i < p.size(); i++){
		unwind(ret, p[i]);
		ret.push_back(p[i]);
	}
	if(ret.size() > 2){
		unwind(ret, pivot);
	}
	return ret;
}

bool radial_compare(point x, point y, point base = point(1, 0)){
	num cx = cp(base, x);
	num cy = cp(base, y);
	
	if(cx == 0) cx = dot(base, y);
	if(cy == 0) cy = dot(base, y);
	if((cx < 0) == (cy < 0)) return ccw(0, x, y);
	
	return cy < 0;
}

num convex_max_dot(const poly& p, point pt){
	int lo = 0;
	int hi = p.size() - 1;
	point base = p[0] - p.back();
	
	while(lo < hi){
		int md = (lo + hi + 1) / 2;
		point v = p[md] - p[md ? md - 1 : p.size() - 1];
		
		if(radial_compare(v, pt * point(0, 1), base)){
			lo = md;
		}else{
			hi = md - 1;
		}
	}
	
	return dot(p[lo], pt);
}

struct dyn_hull{
	dyn_hull(){
	}
	
	void add(point pt){
		poly p(1, pt);
		for(int i = 0; i < hulls.size(); i++){
			if(hulls[i].empty()){
				hulls[i] = hull(p);
				return;
			}
			for(int j = 0; j < hulls[i].size(); j++){
				p.push_back(hulls[i][j]);
			}
			hulls[i].clear();
		}
		hulls.push_back(hull(p));
	}
	
	num max_dot(point pt){
		num ret = 0;
		bool init = false;
		for(int i = 0; i < hulls.size(); i++){
			if(hulls[i].empty()) continue;
			
			num res = convex_max_dot(hulls[i], pt);
			if(!init || res > ret){
				init = true;
				ret = res;
			}
		}
		return ret;
	}
	
	bool empty(){
		return hulls.empty();
	}
	
	vector<poly> hulls;
};

int main(){
	freopen("fencing.in", "r", stdin);
	freopen("fencing.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	poly h0;
	
	for(int i = 0; i < n; i++){
		num x, y;
		cin >> x >> y;
		h0.push_back(point(x, y));
	}
	
	h0 = hull(h0);
	
	dyn_hull h;
	for(int i = 0; i < q; i++){
		int cmd;
		cin >> cmd;
		if(cmd == 1){
			num x, y;
			cin >> x >> y;
			h.add(point(x, y));
		}else{
			num a, b, c;
			cin >> a >> b >> c;
			point pt(a, b);
			
			if((
				dot(h0[0], pt) <= c ||
				-convex_max_dot(h0, -pt) <= c ||
				(!h.empty() && -h.max_dot(-pt) <= c)
			) && (
				dot(h0[0], pt) >= c ||
				convex_max_dot(h0, pt) >= c ||
				(!h.empty() && h.max_dot(pt) >= c)
				)
			){
				cout << "NO" << endl;
			}else{
				cout << "YES" << endl;
			}
		}
	}

	return 0;
}