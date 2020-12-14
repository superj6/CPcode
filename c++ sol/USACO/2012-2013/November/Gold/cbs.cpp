#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 50001, mxk = 10;
typedef array<int, mxk> T; 
int n, k;
T a[mxn], b[mxn << 1];
int dp[mxn], p[mxn];
map<T, int> mp;
int t;

int main(){
	freopen("cbs.in", "r", stdin);
	freopen("cbs.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> k >> n;
	
	for(int j = 0; j < k; j++){
		a[0][j] = mxn;
		for(int i = 1; i <= n; i++){
			char c;
			cin >> c;
			a[i][j] = 2 * (c == '(') - 1 + a[i - 1][j];
		}
	}
	
	ll ret = 0;
	for(int i = 0; i <= n; i++){
		if(!mp.count(a[i])) mp[a[i]] = t++;
		int it = mp[a[i]], w = 0;
		for(int j = 0; j < k; j++){
			w |= b[a[i][j] - 1][j] > p[it];
			b[a[i][j]][j] = i;
		}
		if(w) dp[it] = 1;
		else ret += dp[it]++;
		p[it] = i;
	}
	
	cout << ret << endl;

	return 0;
}