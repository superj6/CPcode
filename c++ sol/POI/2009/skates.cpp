#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

struct T{
	ll s, mn, mx, v;
	
	T friend operator+(T l, T r){
		return {
			l.s + r.s,
			min(l.mn, l.s + r.mn),
			max(l.mx, l.s + r.mx),
			max({l.v, r.v, l.s + r.mx - l.mn})
		};
	}
};

const int mxn = 1 << 18;
int n, m, k, w, q;
T t[mxn << 1];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q >> k >> m;
	w = 1 << (__lg(n - 1) + 1);
	
	for(int i = 0; i < w; i++){
		t[w + i].s = 0;
		t[w + i].mn = (ll)-k * min(n, i);
		t[w + i].mx = (ll)-k * min(n, i + m + 1);
		t[w + i].v = t[w + i].mx - t[w + i].mn;
	}
	
	for(int i = w - 1; i; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	
	while(q--){
		int x, y;
		cin >> x >> y;
		x--;
		t[w + x].s += y, t[w + x].mx += y, t[w + x].v += y;
		for(int i = (w + x) >> 1; i; i >>= 1) t[i] = t[i << 1] + t[i << 1 | 1];
		cout << (t[1].v <= 0 ? "TAK" : "NIE") << endl;
	}

	return 0;
}