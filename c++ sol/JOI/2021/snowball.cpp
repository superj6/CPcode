#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mxn = 200002;
int n, q;
ll a[mxn], f[mxn];
pi b[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	a[0] = -inf, a[n + 1] = inf;
	for(int i = 1; i <= n + 1; i++){
		if(i <= n) cin >> a[i];
		b[i - 1] = {i - 1, i};
	}
	
	sort(b, b + n + 1, [&](pi x, pi y){ 
		return a[x.s] - a[x.f] < a[y.s] - a[y.f];
	});
	
	ll it = 0, x = 0, l = 0, r = 0;
	for(int i = 0; i < q; i++){
		ll z;
		cin >> z;
		x += z;
		for(; it <= n && (z > 0 ? l + x : r - x) >= a[b[it].s] - a[b[it].f]; it++){
			f[b[it].f] += r, f[b[it].s] += l;
			f[(z > 0 ? b[it].f : b[it].s)] += a[b[it].s] - a[b[it].f] - l - r;
		}
		l = max(l, -x), r = max(r, x);
	}
	
	for(; it <= n; it++) f[b[it].f] += r, f[b[it].s] += l;
	
	for(int i = 1; i <= n; i++) cout << f[i] << endl;
	
	return 0;
}