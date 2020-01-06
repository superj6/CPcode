#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long mod = 1000000007;
const int maxn = 100000;
int n;
long long minv[maxn];
long long maxv[maxn];
long long temp[maxn];
long long sum[maxn];
long long ssum[maxn];

int main(){
	freopen("sprinklers.in", "r", stdin);
	freopen("sprinklers.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) minv[i] = sum[i] = n - 1;
	for(int i = 0; i < n; i++){
		long long x, y;
		cin >> x >> y;
		minv[x] = min(minv[x], y);
		maxv[x] = max(maxv[x], y);
		sum[y] = min(sum[y], x);
		temp[y] = max(temp[y], x);
	}
	
	for(int i = n - 2; i >= 0; i--) maxv[i] = max(maxv[i], maxv[i + 1]);
	minv[0] = min(minv[0], maxv[0]);
	for(int i = 1; i < n; i++) minv[i] = min(minv[i], min(minv[i - 1], maxv[i]));
	
	for(int i = n - 2; i >= 0; i--) temp[i] = max(temp[i], temp[i + 1]);
	sum[0] = min(sum[0], temp[0]);
	for(int i = 1; i < n; i++) sum[i] = min(sum[i], min(sum[i - 1], temp[i]));

	ssum[0] = sum[0];
	for(int i = n - 2; i >= 0; i--){
		ssum[i] = (sum[i] * (n - i)) % mod;
		sum[i] += sum[i + 1];
		ssum[i] += ssum[i + 1];

		sum[i] %= mod;
		ssum[i] %= mod;
	}
	
	long long ret = 0;
	for(int i = 0; i < n; i++){
		ret = (ret + ((((maxv[i] + 1) * (maxv[i]) / 2) % mod) * i) % mod) % mod;
		ret = (mod + ret - ((((2 * maxv[i] - minv[i] + 1) * (minv[i]) / 2) % mod) * i) % mod) % mod;
		ret = (mod + ret - (mod + ssum[minv[i]] - ssum[maxv[i]]) % mod) % mod;
		ret = (mod + ret + (((mod + sum[minv[i]] - sum[maxv[i]]) % mod) * (n - maxv[i])) % mod) % mod;
	}
	
	cout << ret << endl;

	return 0;
}