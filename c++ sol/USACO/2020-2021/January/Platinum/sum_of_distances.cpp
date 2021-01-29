#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 200001, mxk = 50000, w = 3;
int n, m, k;
ll d[mxn], iv[mxn], f[mxk][w], a[w], b[w];
vector<pi> v[mxn];
vector<int> g[mxn];
queue<int> q;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k;
	
	iv[0] = iv[1] = 1;
	for(int i = 2; i < mxn; i++) iv[i] = mod - mod / i * iv[mod % i] % mod;
	
	for(int t = 0; t < k; t++){ 
		cin >> n >> m;
		for(int i = 0; i < 2 * n; i++) g[i].clear(), d[i] = 2 * n;
		for(int i = 0; i < m; i++){
			int u, v;
			cin >> u >> v;
			u--, v--;
			for(int j = 0; j < 2; j++){
				g[j * n + u].push_back(!j * n + v);
				g[j * n + v].push_back(!j * n + u);
			}
		}
		d[0] = 0;
		q.push(0);
		while(!q.empty()){
			int c = q.front();
			q.pop();
			v[d[c]].push_back({d[c] < d[(n + c) % (2 * n)], t});
			for(int i : g[c]){
				if(d[i] > d[c] + 1){
					d[i] = d[c] + 1;
					q.push(i);
				}
			}
		}
	}
		
	ll ret = 0;
	for(int i = 0; i < w; i++) a[i] = 1;
	
	for(int i = 0; i < mxn; i++)
	for(int j = 0; j < w; j++){
		ll x = a[j] * (b[j] == k);
		for(pi p : v[i]) if(j < 2 ? (i & 1) == j : !p.f){
			if(!(f[p.s][j]++)) b[j]++;
			else (a[j] *= iv[f[p.s][j] - 1] * f[p.s][j] % mod) %= mod;
		}
		(ret += mod + (1 - 2 * (j == 2)) * i * (mod + a[j] * (b[j] == k) - x) % mod) %= mod;
	}
		
	cout << ret << endl;
	
	return 0;
}