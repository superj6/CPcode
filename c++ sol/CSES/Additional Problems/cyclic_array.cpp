#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
const int maxn = 400000;
long long n, k;
int a[maxn], p[maxn], f[maxn], dp[maxn], dp2[maxn];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	long long m = 0, s = 0;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i + n] = a[i];
	}
 
	for(long long i = 0, s = 0; i < 2 * n; i++){
		s += a[i];
		if(i) p[i] = p[i - 1];
		while(s > k) s -= a[p[i]++];
	}
	
	f[2 * n - 1] = 2 * n - 1;
	for(long long i = 2 * n - 1, s = 0; i >= 0; i--){
		s += a[i];
		if(i < 2 * n - 1) f[i] = f[i + 1];
		while(s > k) s -= a[f[i]--];
	}
	
	int ret = n;
	for(int i = 0; i < 2 * n; i++){
		dp[i] = (p[i] ? dp[p[i] - 1] : i);
		dp2[i] = 1 + (p[i] ? dp2[p[i] - 1] : 0);
		while(i - dp[i] >= n){
			dp[i] = f[dp[i] + 1];
			dp2[i]--;
		}
		if(i - p[dp[i]] + 1 >= n) ret = min(ret, dp2[i]);
	}
	
	cout << ret << endl;
	
	return 0;
}