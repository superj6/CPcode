#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const int maxn = 200002;
ll n, l, r, y;
pi a[maxn];
set<int> s;
int ans[maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> l >> r >> y;
	
	for(int i = 1; i <= n; i++){
		ll x, v, h;
		cin >> x >> v >> h;
		v = (y * h - 1) / v;
		a[i] = {x - v, i};
		a[i + n] = {x + v + 1, -i};
	}
	a[0].f = l, a[2 * n + 1].f = r + 1;
	
	sort(a + 1, a + 2 * n + 1);
	
	for(int i = 1; i <= 2 * n + 1; i++){
		ans[(int)s.size()] += max(min(a[i].f, r + 1LL) - max(a[i - 1].f, l), 0LL);
		if(a[i].s < 0) s.erase(-a[i].s);
		else s.insert(a[i].s);
	}
	
	for(int i = 0; i <= n; i++){
		if(i) ans[i] += ans[i - 1];
		cout << ans[i] << endl;
	}

	return 0;
}