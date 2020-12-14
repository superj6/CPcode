#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int m = 1000001;
ll n, x, y, fx, fy;
ll a[m], b[m], f[m + 1], g[m];

void answer(){
	cin >> x >> y;
	n = y - x + 1;
	
	fx = lower_bound(g, g + m, x) - g;
	fy = lower_bound(g, g + m, y) - g;
	memset(a + fx, 0, (fy - fx + 1) * sizeof(int));
	memset(b + fx, 0, (fy - fx + 1) * sizeof(int));
	a[fx] = b[fx] = min(y, g[fx]) - x + 1;
	a[fy] = b[fy] = y - max(x, g[fy - 1]);
	for(int i = fx + 1; i < fy; i++) a[i] = b[i] = f[i] + f[i + 1];
	
	ll ret = 1;
	for(int i = fy >> 1; i >= fx; i--)
	for(int j = 2 * i; j <= fy && a[i]; j += i){
		ll d = min(a[i], b[j]);
		ret += d, a[i] -= d, b[j] -= d;
	}
	ret = n - ret;
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	f[1] = f[2] = 1, g[1] = f[3] = 2;
	for(int i = 2, j = 3; i < m; i++){
		int k = f[i] + f[i + 1];
		for(int l = 0; l < k && j + l <= m; l++) f[j + l] = i;
		if(j <= m) j += k;
		g[i] = g[i - 1] + k;
	}
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}