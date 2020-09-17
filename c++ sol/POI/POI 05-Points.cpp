/*
  For each set, first reassign points with center of mass as origin, then put points into rings based on their distance from the center
of mass. For each ring, sort points by angle and create a circular string using angles between consecutive points. Now, for two sets to
be equivalent, they must have the same number of rings, all corresponding rings must have the same scale distance and number of points in
each, and each ring must have one's angle string or the reverse of it be a substring of the other, and all rings should have an angle in
common that is the shift of one's string so that it is the substring of the other. You can test the substring constraint by duplicating
one string and using kmp to see if the other is a substring. To not have precision issues, I use some tricks such as scaling points so
center of mass is integer and holding angles as a pair of dot product and cross product, so no decimal values are involved.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<ll, ll>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

pi operator*(int x, pi p){
	return {x * p.f, x * p.s};
}

ll f(pi p){
	return p.f * p.f + p.s * p.s;
}

ll cp(pi x, pi y){
	return x.f * y.s - x.s * y.f;
}

pi ff(pi x, pi y){
	pi p = {x.f * y.f + x.s * y.s, cp(x, y)};
	ll g = max(1ll, __gcd(abs(p.f), abs(p.s)));
	p.f /= g, p.s /= g;
	return p;
}

pi fc(pi p){
	return {(2 * (p.s > 0) - 1) * (abs(p.f) - p.f + abs(p.s)), abs(p.f) + abs(p.s)};
}

const int mxn = 25000;
int n, m, q;
pi s;
pi a[mxn];
ll it[mxn];
vector<pi> v1[mxn], d1[mxn], v2[mxn], d2[mxn];
vector<int> p[mxn];
map<pi, int> mp[2];

void sol(int &n, int&m, vector<pi> v[mxn], vector<pi> d[mxn]){
	cin >> n;
	
	s = {0, 0};
	for(int i = 0; i < n; i++){
		cin >> a[i].f >> a[i].s;
		s = s + a[i];
		v[i].clear(), d[i].clear();
	}
	
	for(int i = 0; i < n; i++){
		a[i] = n * a[i] + -1 * s;
		it[i] = f(a[i]);
	}
	
	sort(it, it + n);
	m = unique(it, it + n) - it;
	
	for(int i = 0; i < n; i++){
		v[lower_bound(it, it + m, f(a[i])) - it].push_back(a[i]);
	}
	
	for(int i = 0; i < m; i++){
		sort(v[i].begin(), v[i].end(), [&](pi x, pi y){
			return cp(fc(x), fc(y)) < 0;
		});
		int k = v[i].size();
		for(int j = 1; j < 2 * k; j++){
			d[i].push_back(ff(v[i][j % k], v[i][(j - 1) % k]));
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	sol(n, m, v1, d1);
	
	for(int t = 0; t < m; t++){
		p[t].push_back(0);
		for(int i = 1, j = 0; i < v1[t].size(); i++){
			while(j && d1[t][i] != d1[t][j]) j = p[t][j - 1];
			p[t].push_back(j += d1[t][i] == d1[t][j]);
		}
	}
	
	cin >> q;
	
	while(q--){
		int nn, mm, w = 0, st;
		sol(nn, mm, v2, d2);
		
		if(nn != n || mm != m || (st = !f(v1[0][0])) != !f(v2[0][0])) goto hell;
		
		mp[0].clear(), mp[1].clear();
		for(int t = st; t < m; t++){
			int k = v1[t].size();
			if(v2[t].size() != k || (unsigned ll)f(v2[st][0]) * f(v1[t][0]) != 
				(unsigned ll)f(v1[st][0]) * f(v2[t][0])) goto hell;

			for(int r = 0; r < 2; r++){
				for(int i = 0, j = 0; i < 2 * k - 1; i++){
					while(j && d1[t][j] != d2[t][i]) j = p[t][j - 1];
					if((j += (d1[t][j] == d2[t][i])) == k){
						mp[r][ff(v1[t][j - 1], v2[t][i % k])]++;
						j = p[t][j - 1];
					}
				}
				reverse(v2[t].begin(), v2[t].end());
				reverse(d2[t].begin(), d2[t].end());
				for(int i = 0; i < k; i++) v2[t][i].f *= -1;
			}
		}
		
		w |= m == st;
		for(int i = 0; i < 2; i++)
		for(auto j : mp[i]){
			w |= j.s == m - st;
		}
		
		hell:
		cout << (w ? "TAK" : "NIE") << endl;
	}
	
	return 0;
}
