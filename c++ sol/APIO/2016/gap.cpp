//#include "gap.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
int t, n;
ll a[mxn];

void MinMax(ll l, ll r, ll *x, ll *y){
	l = lower_bound(a, a + n, l) - a;
	r = upper_bound(a, a + n, r) - a - 1;
	if(l > r) *x = -1, *y = -1;
	else *x = a[l], *y = a[r];
}

void f(ll l, ll r, ll &x, ll &y){
	MinMax(l, r, &x, &y);
}

ll findGap(int t, int n){
	ll l, r, ret = 0;
	f(0, 1e18, l, r);
	if(t & 1){
		for(ll i = 1, x, y; 2 * i < n && r - l > 1; i++, l = x, r = y){
			f(l + 1, r - 1, x, y);
			if(!~x || !~y) break;
			ret = max({ret, r - y, x - l});
		}
	}else{
		for(ll d = (r - l) / (n - 1), i = l + 1; i < r; i += 2 * d){
			ll x, y;
			f(i, min(r - 1, i + 2 * d - 1), x, y);
			if(~x && ~y) ret = max({ret, x - l, y - x}), l = y;
		}
	}
	ret = max(ret, r - l);
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> t >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	cout << findGap(t, n) << endl;

	return 0;
}