#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

template <typename T>
void uq(T &v){
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
}

const int mod = 1234567;
const int maxn = 1 << 16, k = 5, d = 10, l = 4;
int n, m;
int p[maxn], f[maxn], st[maxn], dp2[maxn];
int tre[maxn << 1];
map<int, int> dp[maxn];
vector<int> v[maxn], v2[maxn], g[maxn];
vector<pi> graph[maxn];

void upd(int x){
	for(x = (x + maxn) >> 1; x; x >>= 1){
		tre[x] = (ll)tre[x << 1] * tre[x << 1 | 1] % mod;
	} 
}

void solve(int x, int s){
	vector<int> prv;
	for(int i = st[s]; i < graph[x].size() && graph[x][i].f == s; i++){
		int j = graph[x][i].s;
		prv.push_back(dp[j][s]);
		swap(prv.back(), tre[j + maxn]);
		upd(j);
	}

	dp2[s] = tre[1];
	for(int i : g[s]) solve(x, i);
	
	for(int i = st[s]; i < graph[x].size() && graph[x][i].f == s; i++){
		int j = graph[x][i].s;
		tre[j + maxn] = prv[i - st[s]];
		upd(j);
	}
}

int main(){
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	p[0] = -1;
	v[0].push_back(0);
	for(int i = 1; i < n; i++){
		cin >> p[i];
		v[i].push_back(0);
		graph[p[i]].push_back({0, i});
	}
	
	while(m--){
		char c;
		int x, s = 0;
		cin >> x;
		for(int i = 0; i < k; i++){
			cin >> c;
			s = s << l | (c - '0' + 1);
		}
		v2[x].push_back(s);
		for(int i = k - 1; i; i--, x = p[x]){
			s &= (1 << i * l) - 1;
			v[x].push_back(s);
			graph[p[x]].push_back({s, x});
		}
	}
	
	memset(f, -1, sizeof(f));
	for(int i = 1; i < (maxn << 1); i++) tre[i] = 1;
	
	int ret = 1;
	for(int x = n - 1; ~x; x--){
		f[0] = x;
		g[0].clear();
		st[0] = 0;
		uq(graph[x]);
		for(int i = 0; i < graph[x].size(); i++){
			int s = graph[x][i].f;
			if(f[s] == x) continue;
			
			f[s] = x;
			g[s].clear();
			st[s] = i;
			for(; f[s >> l] != x; s >>= l){
				f[s >> l] = x;
				g[s >> l].assign(1, s);
				st[s >> l] = i;
			}
			g[s >> l].push_back(s);
		}
		
		solve(x, 0);
		
		uq(v[x]), uq(v2[x]);
		for(int i : v[x]){
			int s = i;
			for(; s && s < (1 << l * 3); s <<= l);
			for(int j = 1; j <= d; j++){
				int ss = j << 4 * l | s;
				auto it = lower_bound(v2[x].begin(), v2[x].end(), ss);
				if(it == v2[x].end() || *it != ss){
					for(ss >>= l; f[ss] != x; ss >>= l);
					(dp[x][i] += dp2[ss]) %= mod;
				}
			}
		}
		ret = (ll)ret * d % mod;
	}
	(ret += mod - dp[0][0]) %= mod;
	
	cout << ret << endl;

	return 0;
}