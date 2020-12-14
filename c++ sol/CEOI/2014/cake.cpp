#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<pi, int>
#define f first
#define s second
 
const int mxn = 250002, m = 14;
int n, k, q;
int a[mxn];
int f[m], b[m];
set<pii> s;
 
int ff(int x){
	return find(f, f + m, x) - f;
}
 
void add(int x, int y, int v){
	auto it = s.lower_bound({{y + 1, 0}, 0});
	if(it->f.s <= y) s.insert({{it->f.f, y + 1}, it->s - (y < k) * (y + 1 - it->f.s)}), it = s.erase(it);
	while((--it)->f.s >= x) it = s.erase(it);
	if(it->f.f >= x) s.insert({{x - 1, it->f.s}, it->s - (x > k) * (it->f.f + 1 - x)}), it = s.erase(it);
	s.insert({{y, x}, v});
}
 
int qry(int x){
	pii p = *s.lower_bound({{x, 0}, 0});
	return p.s + (x < k ? p.f.s - x : x - p.f.f);
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		f[m - 1] = i;
		for(int j = m - 2; ~-j; j--) if(a[f[j]] < a[f[j + 1]]) swap(f[j], f[j + 1]);
	} 
	
	a[0] = a[n + 1] = f[1] = n + 1;
	s.insert({{0, 0}, n}), s.insert({{k, k}, 0}), s.insert({{n + 1, n + 1}, n});
	
	for(int i = 1, l = k - 1, r = k + 1; i < n; i++){
		if(a[l] < a[r]) add(l, l, i), l--;
		else add(r, r, i), r++;
	}
	
	cin >> q;
	
	int cnt = 0;
	while(q--){
		char t;
		cin >> t;
		if(t == 'F'){
			int x;
			cin >> x;
			cout << qry(x) << endl;
		}else{
			int x, y;
			cin >> x >> y;
			
			for(int i = ff(x); i < m - 1; i++) swap(f[i], f[i + 1]);
			
			f[m - 1] = x, y++;
			for(int i = m - 2; i >= y; i--) swap(f[i], f[i + 1]);
			
			memcpy(b, f, sizeof(b));
			b[m - 1] = !count(f, f + m - 2, k) * k;
			b[m - 2] = x + ((x < k) - (x > k)) * (qry(x + (x < k) - (x > k)) + 2);
			b[m - 2] *= !count(f, f + m - 2, b[m - 2]);
			sort(b, b + m);
			
			for(int l = find(b, b + m, k) - b, r = l, i = b[++r] - b[--l] - 2; i < n - 1;){
				if(ff(b[l]) > ff(b[r])) add(b[l - 1] + 1, b[l], i += b[l] - b[l - 1]), l--;
				else add(b[r], b[r + 1] - 1, i += b[r + 1] - b[r]), r++;
			}
		}
	}
	
	return 0;
}