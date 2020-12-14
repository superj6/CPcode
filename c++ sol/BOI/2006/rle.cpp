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
#define pb push_back

const int mxn = 2000001;
int n, m, k;
ll a[mxn], b[mxn], g[mxn], f[mxn], fp[mxn], dp[mxn], p[mxn], ff[mxn];
set<pi> s;
vector<int> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	a[0] = g[0] = -1;
	for(int i = 0, j = 0; i < m; i++){
		int x, y = 1;
		cin >> x;
		if(x == j){
			cin >> x >> y;
			if(x != j && !y) j = x;
			else y += 1 + 2 * (x != j);
			i += 2;
		}
		if(a[k] == x) b[k] += y;
		else if(y) k++, a[k] = x, b[k] = y, g[k] = -1;
	}
	
	f[0] = -3;
	for(int i = 0; i < n; i++) s.insert({f[i], i});

	for(int i = 1; i <= k; i++){
		s.erase({f[a[i]], a[i]});
		f[a[i]] += 3 * (b[i] / n + !!(b[i] % n) - b[i] / (n + 2)) - min(3ll, b[i] % (n + 2));
		s.insert({f[a[i]], a[i]});
		dp[i] = s.begin()->f + 3, p[i] = fp[ff[i] = s.begin()->s];
		if(f[a[i]] > dp[i]){
			s.erase({f[a[i]], a[i]});
			f[a[i]] = dp[i], fp[a[i]] = i;
			s.insert({f[a[i]], a[i]});
		} 
	}
	
	for(int i = k; p[i] || ff[i]; i = p[i]) g[p[i]] = ff[i];
	
	for(int i = 0, j = 0; i <= k; i++){
		for(int x = n + 2 * (j != a[i]); b[i] >= x; b[i] -= x){
			v.pb(j), v.pb(a[i]), v.pb(x - 3);
		}
		if(j != a[i] && b[i] <= 3) while(b[i]--) v.pb(a[i]);
		else if(b[i]) v.pb(j), v.pb(a[i]), v.pb(b[i] - 1 - 2 * (j != a[i]));
		if(~g[i]) v.pb(j), v.pb(j = g[i]), v.pb(0);
	}
	
	cout << v.size() << endl;
	cout << v[0];
	for(int i = 1; i < v.size(); i++) cout << " " << v[i];
	cout << endl;

	return 0;
}