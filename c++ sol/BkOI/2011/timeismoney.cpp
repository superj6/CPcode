#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, int>
#define f first
#define s second
 
const int maxn = 200, maxm = 10000;
int n, m;
int it[maxm], u[maxm], v[maxm], a[maxm], b[maxm];
int par[maxn], rnk[maxn];
vector<pi> ans;
 
int find(int x){
	return x == par[x] ? x : par[x] = find(par[x]);
}
 
pi mst(ll x, ll y, bool t = 0){
	for(int i = 0; i < n; i++) par[i] = i, rnk[i] = 0;
	sort(it, it + m, [&](int i, int j){
		return a[i] * x + b[i] * y < a[j] * x + b[j] * y;
	});
 
	pi ret = {0, 0};
	for(int i = 0; i < m; i++){
		int j = it[i];
		int w = find(u[j]), z = find(v[j]);
		if(w != z){
			ret.f += a[j], ret.s += b[j];
			if(t) ans.push_back({u[j], v[j]});
			if(rnk[w] < rnk[z]) swap(w, z);
			rnk[w] += rnk[w] == rnk[z];
			par[z] = w;
		}
	}
	
	return ret;
}
 
pi f(pi x, pi y){
	return x.f * x.s < y.f * y.s ? x : y;
}
 
pi solve(pi l, pi r){
	pi p = mst(r.s - l.s, l.f - r.f);
	if((p.f - l.f) * (r.s - l.s) == (p.s - l.s) * (r.f - l.f)) return f(l, r);
	return f(solve(l, p), solve(p, r));
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		cin >> u[i] >> v[i] >> a[i] >> b[i];
		it[i] = i;
	}
	
	pi ret = solve(mst(0, 1), mst(1, 0));
	mst(ret.s, ret.f, 1);
	
	cout << ret.f << " " << ret.s << endl;
	for(pi i : ans) cout << i.f << " " << i.s << endl;
	
	return 0;
}