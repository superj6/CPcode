#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second
 
const int inf = 0x3f3f3f3f;
const int mxn = 2000;
int n, m;
int u[mxn], v[mxn], a[mxn], b[mxn];
pi d[mxn], ans[mxn];
set<pi> pq;
vector<int> g[mxn];
 
pi f(pi x, pi y){
	return x.f * x.s < y.f * y.s ? x : y;
}
 
void djk(ll x, ll y){
	for(int i = 1; i < n; i++) d[i] = {inf, inf};
	pq.insert({0, 0});
	while(!pq.empty()){
		int c = pq.begin()->s;
		ans[c] = f(ans[c], d[c]);
		pq.erase(pq.begin());
		for(int i : g[c]){
			int j = c ^ u[i] ^ v[i];
			ll dj = d[j].f * x + d[j].s * y, dc = (d[c].f + a[i]) * x + (d[c].s + b[i]) * y;
			if(dj > dc){
				pq.erase({dj, j});
				d[j] = {d[c].f + a[i], d[c].s + b[i]};
				pq.insert({dc, j});
			}
		}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i] >> a[i] >> b[i];
		g[--u[i]].push_back(i);
		g[--v[i]].push_back(i);
	}
	
	for(int i = 0; i < n; i++) ans[i] = {inf, inf};
	for(int i = 0; i <= mxn; i++) djk(i, mxn - i);
	
	for(int i = 1; i < n; i++) cout << (ans[i].f == inf ? -1 : ans[i].f * ans[i].s) << endl;
	
	return 0;
}