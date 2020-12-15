#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const int mxn = 300001;
int n, k;
ll a[mxn];
pi dp[mxn];

pi sol(ll x){
	pi p = dp[0];
	for(int i = 1; i <= n; i++){
		dp[i] = dp[i - 1];
		if(p.f + a[i] - x > dp[i].f) dp[i] = {p.f + a[i] - x, p.s + 1};
		if(dp[i].f - a[i] > p.f) p = {dp[i].f - a[i], dp[i].s};
	}
	return dp[n];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 1; i <= n; i++) cin >> a[i], a[i] += a[i - 1];
	
	ll l = -1, r = 0x3f3f3f3f3f3f3f3f;
	while(r - l > 1){
		ll mid = (l + r) / 2;
		if(sol(mid).s <= k) r = mid; 
		else l = mid;
	}
	
	pi p = sol(r);
	
	cout << (p.f + p.s * r) << endl;

	return 0;
}