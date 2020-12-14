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
const int mxn = 100000;
int n, m;
int s[4];
ll d[4][mxn];
vector<pi> g[mxn], gr[2][mxn];
priority_queue<pi, vector<pi>, greater<pi>> pq;

void djk(ll d[mxn], vector<pi> g[mxn]){
	for(int i = 0; i < n; i++){
		if(d[i] != inf || !g[i].empty()) pq.push({d[i], i});
	} 
	while(!pq.empty()){
		ll c = pq.top().s, dd = pq.top().f;
		pq.pop();
		if(d[c] != dd) continue;
		for(pi i : g[c]){
			if(d[i.f] > dd + i.s) pq.push({d[i.f] = dd + i.s, i.f});
		} 
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < 4; i++){
		cin >> s[i];
		s[i]--;
	}
	
	for(int i = 0; i < m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	memset(d, 0x3f, sizeof(d));
	for(int i = 0; i < 3; i++){
		d[i][s[i]] = 0;
		djk(d[i], g);
	}
	memcpy(d[3], d[2], sizeof(d[2]));
	
	for(int i = 0; i < n; i++)
	for(pi j : g[i])
	for(int l = 0; l < 2; l++){
		if(d[0][s[1]] == d[l][i] + j.s + d[!l][j.f]){
			gr[l][i].push_back({j.f, 0});
		}
	}
	
	ll ret = inf;
	for(int i = 0; i < 2; i++){
		djk(d[2 + i], gr[i]), djk(d[2 + i], g);
		ret = min(ret, d[2 + i][s[3]]);
	}
	
	cout << ret << endl;
	
	return 0;
}