#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

const ll inf = 0x3f3f3f3f3f3f3f3f;
const int mxn = 100000, mxk = 5;
int n, m, k;
ll d[1 << mxk][mxn];
vector<pi> g[mxn];
priority_queue<pi, vector<pi>, greater<pi>> pq;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m;
	
	memset(d, 0x3f, sizeof(d));
	memset(d[0], 0, sizeof(d[0]));
	for(int i = 0; i < k; i++){
		int x;
		cin >> x;
		d[1 << i][--x] = 0;
	}
	
	for(int i = 0; i < m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	ll ret = inf;
	for(int l = 1; l < (1 << k); l++){
		for(int i = 0; i < n; i++){
			for(int j = (l - 1) & l; j; j = (j - 1) & l){
				d[l][i] = min(d[l][i], d[j][i] + d[l ^ j][i]);
			} 
			if(l == (1 << k) - 1) ret = min(ret, d[l][i]);
			else if(d[l][i] != inf) pq.push({d[l][i], i});
		}
		while(!pq.empty()){
			ll dc = pq.top().f, c = pq.top().s;
			pq.pop();
			if(dc != d[l][c]) continue;
			for(pi i : g[c]){
				if(dc + i.s < d[l][i.f]){
					pq.push({d[l][i.f] = dc + i.s, i.f});
				}
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}