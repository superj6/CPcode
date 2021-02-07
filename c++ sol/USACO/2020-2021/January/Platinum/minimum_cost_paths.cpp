#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define pii pair<ll, pi>
#define f first
#define s second

const int mxn = 200000;
int n, m, q;
ll a[mxn], ans[mxn];
vector<pii> dp;
vector<pi> v[mxn];

ll f(pi p, ll x, ll y){
	return x * x * (y - p.f) + x * a[p.f] + p.s;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> m >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	cin >> q;
	
	for(int i = 0; i < q; i++){
		int x, y;
		cin >> y >> x;
		v[--x].push_back({y, i});
	}
	
	dp.push_back({1, {0, -a[0]}});
	for(int i = 0; i < n; i++){
		while(dp.size() > 1){
			pi p = dp.back().s;
			int x = dp.end()[-2].f;
			if(f(p, x, i) + a[i] <= f(p, x + 1, i)){
				dp.pop_back();
				continue;
			}
			int l = x, r = dp.back().f;
			while(r - l > 1){
				int mid = (l + r) / 2;
				if(f(p, mid, i) + a[i] >= f(p, mid + 1, i)) l = mid;
				else r = mid;
			}
			dp.back().f = r;
			break;
		}
		
		int x = dp.back().f;
		if(x < m) dp.push_back({m, {i, f(dp.back().s, x, i) - x * a[i]}});

		for(pi j : v[i]){
			int x = lower_bound(dp.begin(), dp.end(), (pii){j.f, {-1, 0}}) - dp.begin();
			ans[j.s] = f(dp[x].s, j.f, i);
		}
	}
	
	for(int i = 0; i < q; i++) cout << ans[i] << endl;
	
	return 0;
}