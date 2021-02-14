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

const int mxn = 5001;
int n;
ll a[mxn], b[mxn], f[mxn], dp[mxn];

void add(int x, int y){
	for(; x <= n; x += x & -x) b[x] += y;
}

int qry(int x){
	int ret = 0;;
	for(; x; x -= x & -x) ret += b[x];
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	
	for(int i = 1, x; i <= n; i++) cin >> x, a[x] = i;
	
	for(int i = 1; i <= n; i++){
		add(a[i], 1);
		f[i] = i - qry(a[i]);
	}
	for(int i = 1; i <= n; i++) add(a[i], -1);
	
	for(int i = 1; i <= n; i++){
		dp[i] = 0x3f3f3f3f3f3f3f3f;
		for(ll j = i, x = 0; j; j--){
			x += i - j - 2 * qry(a[j]) + f[j];
			dp[i] = min(dp[i], x + dp[j - 1]);
			add(a[j], 1);
		}
		for(int j = 1; j <= i; j++) add(a[j], -1);
	}
	
	cout << dp[n] << endl;
	
	return 0;
}