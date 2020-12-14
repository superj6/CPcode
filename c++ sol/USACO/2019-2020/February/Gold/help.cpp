#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int maxn = 200001;
int n;
int dp[maxn], p[maxn];
pi a[maxn];

int main(){
	freopen("help.in", "r", stdin);
	freopen("help.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	p[0] = 1;
	for(int i = 0; i < n; i++){
		cin >> a[i].f >> a[i].s;
		dp[a[i].f]++, dp[a[i].s]--;
		p[i + 1] = ((long long)2 * p[i]) % mod;
	}
	for(int i = 1; i < 2 * n; i++) dp[i] += dp[i - 1];
	int ret = 0;
	for(int i = 0; i < n; i++) ret = (ret + p[n - dp[a[i].f - 1] - 1]) % mod;
	
	cout << ret << endl;

	return 0;
}