/*
  When you are bounded by a large element on one side, that side will not move until you hit a larger element on the other side.
Because you are only updating an element to be in the top 10 largest, that means you only need to update times after you come into
contact with the element, and you only have to worry about the ranges between elements larger than it, so you can just recompute
all the elements after coming into contact with one of the top 10 by updating a range of elements at once. To do this, hold a set
containing ranges of elements such that the times are increasing consecutively within the range. When updating a range, you can just
cut the end intervals and erase all intervals strictly within the one you are adding, and you can show this is O(lgn) amortized.
For each range you hold the largest time of an element in the range, along with the opposite endpoint when the range is set. This
is because when recomputing the top 10, if the updated element was the first top 10 touched, you also need to update the range
starting at the opposite endpoint when it first touched the updated element even if it is not in the top 10. You can then just 
answer queries by finding the time by querying the interval the element is currently in.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<pi, pi>
#define f first
#define s second
 
const int mxn = 250002, m = 14;
int n, k, q;
int a[mxn];
int f[m], b[m];
set<pii> s;
 
int ff(int x){
	return x < 1 || x > n ? -1 : find(f, f + m - 4, x) - f;
}
 
void add(int x, int y, int v, int w){
	auto it = s.lower_bound({{y + 1, 0}, {0, 0}});
	if(it->f.s <= y) s.insert({{it->f.f, y + 1}, {it->s.f - (y < k) * (y + 1 - it->f.s), it->s.s}}), it = s.erase(it);
	while((--it)->f.s >= x) it = s.erase(it);
	if(it->f.f >= x) s.insert({{x - 1, it->f.s}, {it->s.f - (x > k) * (it->f.f + 1 - x), it->s.s}}), it = s.erase(it);
	s.insert({{y, x}, {v, w}});
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		f[m - 3] = i;
		for(int j = m - 4; ~j; j--) if(a[f[j]] < a[f[j + 1]]) swap(f[j], f[j + 1]);
	} 
	
	a[0] = a[n + 1] = f[m - 1] = n + 1;
	s.insert({{0, 0}, {n, n + 1}});
	s.insert({{k, k}, {0, k}});
	s.insert({{n + 1, n + 1}, {n, 0}});
	
	for(int i = 1, l = k - 1, r = k + 1; i < n; i++){
		if(a[l] < a[r]) add(l, l, i, r), l--;
		else add(r, r, i, l), r++;
	}
	
	cin >> q;
	
	int cnt = 0;
	while(q--){
		char t;
		cin >> t;
		if(t == 'F'){
			int x;
			cin >> x;
			pii p = *s.lower_bound({{x, 0}, {0, 0}});
			cout << (x < k ? p.s.f + p.f.s - x : p.s.f + x - p.f.f) << endl;
		}else{
			int x, y;
			cin >> x >> y;
			y--;
			
			int z = ff(x);
			if(z != m) for(int i = z; i < m - 3; i++) swap(f[i], f[i + 1]);
			
			f[m - 3] = x;
			for(int i = m - 4; i >= y; i--) swap(f[i], f[i + 1]);
			
			int l = 0, r = n + 1;
			for(int i = 0; i < m - 4; i++){
				if(f[i] < k) l = max(l, f[i]);
				if(f[i] > k) r = min(r, f[i]);
			}
			
			memcpy(b, f, sizeof(b));
			b[m - 3] = !count(f, f + m - 4, k) * k;
			b[m - 4] = s.lower_bound({{x + (x < k) - (x > k), 0}, {0, 0}})->s.s;
			if(b[m - 4] == k) b[m - 4] += (x < k) - (x > k);
			b[m - 4] *= !count(f, f + m - 4, b[m - 4]);
			sort(b, b + m);
			
			l = lower_bound(b, b + m, k) - b;
			r = l-- + 1;
			
			for(int i = b[r] - b[l] - 2; i < n - 1;){
				if(ff(b[l]) > ff(b[r])) add(b[l - 1] + 1, b[l], i += b[l] - b[l - 1], b[r]), l--;
				else add(b[r], b[r + 1] - 1, i += b[r + 1] - b[r], b[l]), r++;
			}
		}
	}
	
	return 0;
}
