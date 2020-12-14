#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define pii pair<int, pi>
#define f first
#define s second

const int maxn = 100001;
int n;
pi a[maxn], dp[maxn];
pii l[maxn];
int s, e;

ll sq(ll x){
	return x * x;
}

bool cp(pii x, pii y, pii z){
	return (x.s.f - z.s.f) * (y.s.s - x.s.s) >= (x.s.f - y.s.f) * (z.s.s - x.s.s);
}

ll f(int x, ll y){
	return l[x].s.f * y + l[x].s.s;
}

void g(ll x, ll y, int z){
	while(e - s > 1 && cp(l[e - 2], l[e - 1], {z, {x, y}})) e--;
	l[e++] = {z, {x, y}};
}

pi solve(ll x){
	s = e = 0;
	g(-2 * (a[0].f - 1), sq(a[0].f - 1), 0);
	for(int i = 1; i <= n; i++){
		while(e - s > 1 && f(s, a[i - 1].s) >= f(s + 1, a[i - 1].s)) s++;
		dp[i] = {f(s, a[i - 1].s) + sq(a[i - 1].s) + x, dp[l[s].f].s + 1};
		g(-2 * (a[i].f - 1), dp[i].f + sq(a[i].f - 1) - sq(max((ll)0, a[i - 1].s - a[i].f + 1)), i);
	}
	return dp[n];
}

ll take_photos(int N, int m, int k, vector<int> x, vector<int> y){
	for(int i = 0; i < N; i++) a[i] = {min(x[i], y[i]), max(x[i], y[i])};
	
	sort(a, a + N, [&](pi x, pi y){
		return x.f == y.f ? x.s > y.s : x.f < y.f;
	});
	
	n = 1;
	for(int i = 1; i < N; i++) if(a[i].s > a[n - 1].s) a[n++] = a[i];
	
	ll l = 0, r = sq(m);
	while(r - l > 1){
		ll mid = (l + r) / 2;
		if(k <= solve(mid).s) l = mid;
		else r = mid;
	}
	
	return solve(l).f - k * l;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<int> x(n), y(n);
	for(int i = 0; i < n; i++) cin >> x[i] >> y[i];
	
	cout << take_photos(n, m, k, x, y) << endl;

	return 0;
}