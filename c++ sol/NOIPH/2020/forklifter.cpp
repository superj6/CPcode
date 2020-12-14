#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

const int w = 6;
const pi d[w] = {{0, -1}, {0, 1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}};
ll n, m, k;
vector<vector<ll>> a, b;
vector<pi> v;
auto cmp = [](pi x, pi y){return b[x.f][x.s] < b[y.f][y.s];};
priority_queue<pi, vector<pi>, decltype(cmp)> pq(cmp);

ll sol(ll x){
	b = a;
	ll ret = 0;
	if(k){
		for(pi i : v) pq.push(i);
		while(!pq.empty()){
			pi c = pq.top();
			pq.pop();
			for(int j = 0; j < w; j++){
				pi p = c + d[j];
				if(p.f < 0 || p.s < 0 || p.f >= n || p.s >= m) continue;
				ll y = max(0ll, b[c.f][c.s] - x - b[p.f][p.s]);
				ret += min(k + 1 - ret, y), b[p.f][p.s] += y;
				if(y) pq.push(p);
			}
		}
	}else{
		for(pi c : v)
		for(int j = 0; j < w; j++){
			pi p = c + d[j];
			if(p.f < 0 || p.s < 0 || p.f >= n || p.s >= m) continue;
			ll y = max(0ll, b[c.f][c.s] - x - b[p.f][p.s]);
			ret += min(k + 1 - ret, y), b[p.f][p.s] += y;
		}
	}
	return ret;
}

void answer(){
	cin >> n >> m >> k;
	
	a.assign(n, vector<ll>(m));
	v.clear();
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		cin >> a[i][j];
		v.push_back({i, j});
	}
	
	if(!k) sort(v.begin(), v.end(), [&](pi x, pi y){
		return a[x.f][x.s] > a[y.f][y.s];	
	});
	
	ll l = -1, r = 1e12;
	while(r - l > 1){
		ll mid = (l + r) / 2;
		if(sol(mid) <= k) r = mid;
		else l = mid;
	}
	
	cout << r << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}