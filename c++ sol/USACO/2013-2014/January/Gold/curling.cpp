#include <iostream>
#include <cstdio>
#include <algorithm>
#include <complex>
#include <vector>
using namespace std;
#define endl '\n'

typedef complex<long long> point;
typedef vector<point> poly;

long long cp(point a, point b, point c){
	return imag(conj(a - c) * (b - c));
}

bool ccweq(point a, point b, point c){
	return 0 <= cp(a, b, c);
}

long long dot(point a, point b, point c){
	return real(conj(a - c) * (b - c));
}

point pivot;
bool pointCmp(point a, point b){
	return make_pair(a.real(), a.imag()) < make_pair(b.real(), b.imag());
}

bool angleCmp(point a, point b){
	long long c = cp(pivot, a, b);
	return c == 0 && dot(a, a, pivot) < dot(b, b, pivot) || c > 0;
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

bool inTriangle(point a, point b, point c, point pt){
	long long s1 = abs(cp(b, c, a));
	long long s2 = abs(cp(a, b, pt)) + abs(cp(b, c, pt)) + abs(cp(c, a, pt));
	return s1 == s2;
}

bool inside(poly p, point a){
	int n = p.size() - 1;
	if(cp(p[1], a, p[0]) != 0 && ccweq(p[1], a, p[0]) != ccweq(p[1], p[n], p[0])) return false;
	if(cp(p[n], a, p[0]) != 0 && ccweq(p[n], a, p[0]) != ccweq(p[n], p[1], p[0])) return false;
	if(cp(p[1], a, p[0]) == 0) return dot(a, a, p[0]) <= dot(p[1], p[1], p[0]) && dot(p[1], a, p[0]) >= 0;

	int l = 0, r = n;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(ccweq(p[mid], a, p[0])) l = mid;
		else r = mid;
	}
	
	return inTriangle(p[l], p[l + 1], p[0], a);
	
}

int main(){
	freopen("curling.in", "r", stdin);
	freopen("curling.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	poly a, b;
	
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		a.push_back(point(x, y));
	}
	
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		b.push_back(point(x, y));
	}
	
	poly hulla = hull(a), hullb = hull(b);
	
	int suma = 0, sumb = 0;
	
	for(int i = 0; i < n; i++){
		if(inside(hulla, b[i])) suma++;
		if(inside(hullb, a[i])) sumb++;
	}
	
	cout << suma << " " << sumb << endl;
	
	return 0;
}