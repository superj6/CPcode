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