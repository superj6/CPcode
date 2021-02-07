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
const int mxn = 2000;
int n, m;
ll a[mxn], b[mxn], w[mxn], d[mxn], dp[mxn], dp2[mxn], f[mxn];
vector<int> v;
vector<int> g[mxn], gr[mxn];
priority_queue<pi, vector<pi>, greater<pi>> pq;

int main(){
	//freopen("roadhelp.in", "r", stdin);
	//freopen("roadhelp.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		cin >> a[i] >> b[i] >> w[i];
		g[--a[i]].push_back(i);
		g[--b[i]].push_back(i);
	}
	
	for(int t = 0; t < n; t++){
		dp[t] = 1;
		memset(d, 0x3f, sizeof(d));
		pq.push({d[t] = 0, t});
		v.clear();
		while(!pq.empty()){
			int dd = pq.top().f, c = pq.top().s;
			pq.pop();
			if(dd != d[c]) continue;
			v.push_back(c);
			for(int i : g[c]){
				int x = a[i] ^ b[i] ^ c;
				if(d[x] > dd + w[i]){
					dp[x] = dp[c];
					pq.push({d[x] = dd + w[i], x});
				}else if(d[x] == dd + w[i]){
					(dp[x] += dp[c]) %= mod;
				}
			}
		}
		
		reverse(v.begin(), v.end());
		for(int i : v){
			dp2[i] = 1;
			for(int j : g[i]){
				int x = a[j] ^ b[j] ^ i;
				if(d[i] + w[j] == d[x]){
					dp2[i] += dp2[x];
					(f[j] += dp[i] * dp2[x]) %= mod;
				} 
			}
		}
	}
	
	for(int i = 0; i < m; i++) cout << f[i] << endl;
	
	return 0;
}