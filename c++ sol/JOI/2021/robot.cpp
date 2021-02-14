#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<ll, pi>
#define f first
#define s second

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mxn = 100000;
int n, m;
vector<ll> v[mxn], dp[mxn];
vector<pii> g[mxn];
priority_queue<pii, vector<pii>, greater<pii>> pq;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int x, y, w, z;
		cin >> x >> y >> w >> z;
		x--, y--, w--;
		g[x].push_back({w, {y, z}});
		g[y].push_back({w, {x, z}});
	}
	
	for(int i = 0; i < n; i++){
		g[i].push_back({-1, {i, inf}});
		sort(g[i].begin(), g[i].end());
		v[i].resize(g[i].size() + 1);
		dp[i].resize(g[i].size(), inf);
		for(int j = 1; j < v[i].size(); j++){
			v[i][j] = g[i][j - 1].s.s + v[i][j - 1];
		} 
	}
	
	pq.push({dp[0][0] = 0, {0, 0}});
	while(!pq.empty()){
		ll d = pq.top().f, c = pq.top().s.f, x = pq.top().s.s;
		pq.pop();
		if(d != dp[c][x]) continue;
		if(c == n - 1){
			cout << d << endl;
			return 0;
		}
		for(int i = 1; i < g[c].size(); i++){
			pii p = g[c][i];
			int y = lower_bound(g[p.s.f].begin(), g[p.s.f].end(), 
				(pii){p.f, {c, p.s.s}}) - g[p.s.f].begin();
			int l = lower_bound(g[c].begin(), g[c].end(), 
				(pii){p.f, {0, 0}}) - g[c].begin();
			int r = upper_bound(g[c].begin(), g[c].end(),
				(pii){p.f, {inf, inf}}) - g[c].begin();
			ll z = v[c][r] - v[c][l] - 
				(x != i && x >= l && x < r) * g[c][x].s.s - p.s.s;
			
			if(dp[p.s.f][y] > d + p.s.s){
				pq.push({dp[p.s.f][y] = d + p.s.s, {p.s.f, y}});
			}
			if(dp[p.s.f][0] > d + z && z < p.s.s){
				pq.push({dp[p.s.f][0] = d + z, {p.s.f, 0}});
			}
		}
	}
	
	cout << -1 << endl;
	
	return 0;
}