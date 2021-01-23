#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<pi, pi>
#define f first
#define s second

const int mxn = 400000;
int n, m, q;
int a[mxn], b[mxn], p[mxn], f[mxn], dp[mxn];
stack<pii> stk;

int fnd(int x){
	return x == p[x] ? x : fnd(p[x]);
}

void unf(int x, int y){
	x = fnd(x), y = fnd(y);
	stk.push({{x, y}, {f[x], f[y]}});
	if(x != y){
		if(f[x] < f[y]) swap(x, y);
		f[x] += f[x] == f[y], p[y] = x;
	}
}

void fnu(){
	pii x = stk.top();
	stk.pop();
	p[x.f.f] = x.f.f, p[x.f.s] = x.f.s;
	f[x.f.f] = x.s.f, f[x.f.s] = x.s.s;
}

bool add(int x){
	unf(a[x], b[x] + n), unf(a[x] + n, b[x]);
	return fnd(a[x]) == fnd(a[x] + n);
}

void del(){
	fnu(), fnu();
}

void sol(int l, int r, int x, int y, int z){
	if(l > r) return;
	
	int mid = (l + r) / 2, zz = z;
	for(int i = l; i < mid; i++) zz |= add(i);
	
	dp[mid] = y;
	int w = zz;
	while(dp[mid] > max(mid, x) && !w) w |= add(--dp[mid]);
	
	for(int i = dp[mid]; i < y; i++) del();
	zz |= add(mid);
	sol(mid + 1, r, max(mid + 1, dp[mid]), y, zz);
	
	zz = z;
	for(int i = l; i <= mid; i++) del();
	for(int i = y; i > dp[mid]; i--) zz |= add(i - 1);
	sol(l, mid - 1, x, dp[mid], zz);
	
	for(int i = y; i > dp[mid]; i--) del();
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> q;
	
	for(int i = 0; i < m; i++) cin >> a[i] >> b[i], a[i]--, b[i]--;
	
	for(int i = 0; i < 2 * n; i++) p[i] = i;
	
	sol(0, m - 1, 0, m, 0);
	
	while(q--){
		int x, y;
		cin >> x >> y;
		x--, y--;
		cout << (y < dp[x] ? "YES" : "NO") << endl;
	}
	
	return 0;
}