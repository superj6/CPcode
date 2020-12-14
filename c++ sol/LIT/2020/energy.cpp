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

const int mxn = 10000, mxk = 31;
int n, m, k;
int a[mxn];
int dp[mxn][mxk], vis[mxn][mxk];
vector<pi> g[mxn];
auto cmp = [](pi x, pi y){ return dp[x.f][x.s] > dp[y.f][y.s];};
priority_queue<pi, vector<pi>, decltype(cmp)> pq(cmp);

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 0; i < m; i++){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	
	memset(dp, 0x3f, sizeof(dp));
	dp[0][k] = 0;
	pq.push({0, k});
	while(!pq.empty()){
		int c = pq.top().f, x = pq.top().s;
		pq.pop();
		if(vis[c][x]) continue;
		vis[c][x] = 1;
		
		if(a[c] && x < k && dp[c][x] + a[c] < dp[c][x + 1]){
			dp[c][x + 1] = dp[c][x] + a[c];
			pq.push({c, x + 1});
		}
		
		for(pi i : g[c]){
			if(x >= i.s && dp[c][x] < dp[i.f][x - i.s]){
				dp[i.f][x - i.s] = dp[c][x];
				pq.push({i.f, x - i.s});
			}
		}
	}
	
	for(int i = 1; i < n; i++){
		int ret = *min_element(dp[i], dp[i] + k + 1);
		cout << (ret == 0x3f3f3f3f ? -1 : ret);
		if(i < n - 1) cout << " ";
	}
	cout << endl;

	return 0;
}