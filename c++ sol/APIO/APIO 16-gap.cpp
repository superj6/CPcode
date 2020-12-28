/*
	For the first subtask, realize you can just first get the left and right bounds of the array, then keep
getting closest values to the right of the left bound and left of the right bound. For the second subtask, realize
by the pigeon hole principle the answer will be at least d = (r - l) / (n - 1), where l and r are the left and 
right bounds of the array. This is because either the elements are equally spaced with one element per interval of
length d, or if there is more than one element per interval, that means another interval must be empty and the
largest gap will stretch across the empty interval. This means we can just query every interval of length d and see
if the largest gap is right most value previously, the left most value in the interval, or the different between
the left and right value in the interval. However this barely didn't get full score, so I instead queried intervals
of length 2 * d and that worked. I assume it is similar reasoning since you are getting two values per interval, so
you can still apply pigeon hole. In fact, I hoped to get the same code to work for both subtasks using 2 * d length
intervals, but it would barely ask too many queries for subtask 1.
*/

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