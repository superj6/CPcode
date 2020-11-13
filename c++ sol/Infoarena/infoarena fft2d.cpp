/*
  Realize that when traveling between two layers on the graph, the list of reachable nodes starting from one layer consists of a range
of bits that can be toggled from the original nodes index based on the which two layers of the graph you are travelling between. This
means you can do dp from left to right where you keep track of how many starting nodes the current one can reach that none of the 
previous marked nodes can, and subtract overcounting by holding for different bit toggling ranges the sum of the reachable starting nodes.
Then you can just sum the results of each node for how many it can reach from the start multiplied by all the nodes at the end it can
reach.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 29, mxm = 100000;
int n, m;
int a[mxm], b[mxm], it[mxm];
map<int, ll> dp[mxn][mxn];

int main(){
	freopen("fft2d.in", "r", stdin);
	freopen("fft2d.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	n--;
	
	for(int i = 0; i < m; i++){
		cin >> a[i] >> b[i];
		it[i] = i;
	}
	
	sort(it, it + m, [&](int x, int y){
		return a[x] < a[y];	
	});
	
	ll ret = 1ll << (2 * n);
	for(int i = 0; i < m; i++){
		ll x = it[i], y = 1 << a[x];
		for(int j = a[x] - 1, v = b[x]; ~j; j--){
			int l = 1 << (n - j - 1);
			if(v & l) v ^= l;
			y -= dp[j][n - a[x]][v];
		}
		for(int j = n - a[x] - 1, v = b[x]; ~j; j--){
			if(v & (1 << j)) v ^= 1 << j;
			dp[a[x]][j][v] += y;
		}
		ret -= y << (n - a[x]);
	}
	
	cout << ret << endl;

	return 0;
}
