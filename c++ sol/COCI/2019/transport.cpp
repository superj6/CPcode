#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<ll>
#define all(x) x.begin(), x.end()

void mrg(vi &x, vi &y){
	vi v(x.size() + y.size());
	merge(all(x), all(y), v.begin());
	swap(x, v);
}

const int mxn = 100000;
int n;
ll a[mxn], s[mxn], s1[mxn], s2[mxn], sz[mxn], vis[mxn];
vi v1, v2, r1, r2;
vector<pi> g[mxn];

int dfsc(int c, int p){
	sz[c] = 1;
	for(pi i : g[c]) if(i.f != p && !vis[i.f]) sz[c] += dfsc(i.f, c);
	return sz[c];
}

int dfsc2(int c, int p){
	for(pi i : g[c]){
		if(i.f == p || vis[i.f] || 2 * sz[i.f] <= sz[c]) continue;
		sz[i.f] = sz[c];
		return dfsc2(i.f, c);
	}
	return c;
}

void dfs(int c, int p){
	s1[c] = min(s1[c], s[c]), s2[c] = max(s2[c], s[c] += a[c]);
	r1.push_back(s1[c]);
	if(s[c] >= s2[c]) r2.push_back(s[c]);
	for(pi i : g[c]){
		if(i.f == p || vis[i.f]) continue;
		s[i.f] = s[c] - i.s, s1[i.f] = s1[c], s2[i.f] = s2[c];
		dfs(i.f, c);
	}
}

ll f(vi &x, vi &y){
	ll nx = x.size(), ny = y.size(), ret = nx * (ny - 1);
	for(int i = 0, j = ny - 1; i < nx; i++){
		while(~j && x[i] + y[j] >= 0) j--;
		ret -= j;
	}
	return ret;
}

ll sol(int c){
	dfsc(c, -1);
	vis[c = dfsc2(c, -1)] = 1;
	
	s[c] = s1[c] = s2[c] = 0;
	v1.assign(1, s1[c]), v2.assign(1, a[c]);
	ll ret = -f(v1, v2);
	for(pi i : g[c]){
		if(vis[i.f]) continue;
		s[i.f] = s[c] - i.s, s1[i.f] = s1[c], s2[i.f] = s2[c];
		r1.clear(), r2.clear();
		dfs(i.f, c);
		
		for(ll &j : r2) j += a[c];
		sort(all(r1)), sort(all(r2));
		ret -= f(r1, r2);
		mrg(v1, r1), mrg(v2, r2);
	}
	ret += f(v1, v2);
	
	for(pi i : g[c]) if(!vis[i.f]) ret += sol(i.f);
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n - 1; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	cout << sol(0) << endl;

	return 0;
}