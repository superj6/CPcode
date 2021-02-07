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

const int mxn = 100001;
int n, k;
int a[mxn], b[mxn], lp[mxn], vis[mxn];
vector<int> p, d;
vector<pi> v[mxn];

vector<pi> ff(int x){
	vector<pi> f;
	while(~-x){
		int y = lp[x], z = 1;
		while(lp[x] == y) x /= y, z *= y;
		f.push_back({y, z});
	}
	return f;
}

int main(){
	freopen("robdan.in", "r", stdin);
	freopen("robdan.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i], a[i]--;
	
	for(int i = 2; i <= n; i++){
		if(!lp[i]) p.push_back(lp[i] = i);
		for(int j = 0; j < p.size() && p[j] <= lp[i] && i * p[j] <= n; j++){
			lp[i * p[j]] = p[j];
		}
	}
	
	for(int i = 0; i < n; i++) if(!vis[i]){
		int x = 0;
		for(int j = i; !vis[j]; j = a[j]) x++, vis[j] = 1;
		vector<pi> f = ff(b[k] = x);
		for(pi j : f) v[j.f].push_back({j.s, k});
		k++;
	}
	
	for(int i = 1; i <= n; i++) sort(v[i].begin(), v[i].end(), greater<pi>());
	
	ll p = 1, q = 1;
	for(int i = 0; i < k; i++){
		vector<pi> f = ff(b[i]);
		for(int j = 1; j < b[i]; j++){
			vector<pi> f1 = ff(j), f2 = ff(b[i] - j);
			
			d.clear();
			for(pi l : f) d.push_back(l.f);
			for(pi l : f1) d.push_back(l.f);
			for(pi l : f2) d.push_back(l.f);
			
			sort(d.begin(), d.end());
			d.erase(unique(d.begin(), d.end()), d.end());
			
			ll pp = 1, qq = 1;
			for(int l : d){
				int x = 1;
				int it = 0;
				while(it < v[l].size() && v[l][it].s == i) it++;
				if(it < v[l].size()) x = max(x, v[l][it].f);

				it = lower_bound(f1.begin(), f1.end(), (pi){l, 0}) - f1.begin();
				if(it < f1.size() && f1[it].f == l) x = max(x, f1[it].s);
				
				it = lower_bound(f2.begin(), f2.end(), (pi){l, 0}) - f2.begin();
				if(it < f2.size() && f2[it].f == l) x = max(x, f2[it].s);
				
				int y = 1;
				if(!v[l].empty()) y = v[l][0].f;
				
				int g = __gcd(x, y);
				x /= g, y /= g;
				pp *= x, qq *= y;
			}
			
			if((__int128)pp * q < (__int128)p * qq) p = pp, q = qq;
		}
		
		for(pi j : f) if(v[j.f].size() > 1){
			int z = v[j.f][v[j.f][0].f == j.s].s;
			vector<pi> f1 = ff(b[z]), f2 = ff(b[i] + b[z]);
			
			d.clear();
			for(pi l : f) d.push_back(l.f);
			for(pi l : f1) d.push_back(l.f);
			for(pi l : f2) d.push_back(l.f);
			
			sort(d.begin(), d.end());
			d.erase(unique(d.begin(), d.end()), d.end());
			
			ll pp = 1, qq = 1;
			for(int l : d){
				int x = 1;
				
				int it = lower_bound(f2.begin(), f2.end(), (pi){l, 0}) - f2.begin();
				if(f2[it].f == l) x = f2[it].s;
				
				it = 0;
				while(it < v[l].size() && (v[l][it].s == i || v[l][it].s == z)) it++;
				if(it < v[l].size()) x = max(x, v[l][it].f);
				
				int y = 1;
				if(!v[l].empty()) y = v[l][0].f;
				
				int g = __gcd(x, y);
				x /= g, y /= g;
				pp *= x, qq *= y;
			}
			
			if((__int128)pp * q < (__int128)p * qq) p = pp, q = qq;
		}
	}
	
	cout << p << " " << q << endl;
	
	return 0;
}