#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
const int mod = 1000000007;
 
long long modpow(long long b, int e){
	long long ret = 1;
	for(int i = 0; (1 << i) <= e; i++){
		if((1 << i) & e) ret = (ret * b) % mod;
		b = (b * b) % mod;
	}
	return ret;
}
 
const int maxn = 500;
int n;
string s;
long long f[maxn], rf[maxn];
long long dp[maxn][maxn];
 
void init(){
	f[0] = rf[0] = 1;
	for(int i = 1; i <= maxn / 2; i++){
		f[i] = i * f[i - 1] % mod;
		rf[i] = modpow(f[i], mod - 2);
	}
}
 
long long C(int x, int y){
	return f[x] * rf[y] % mod * rf[x - y] % mod;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	init();
	
	cin >> s;
	n = s.size();
	
	for(int i = 0; i < n; i++)
	for(int j = i - 1; j >= 0; j -= 2)
	for(int k = j; k < i; k += 2){
			dp[j][i] += (s[i] == s[k]) * C((i - j + 1) / 2, (i - k + 1) / 2) *  (j < k ? dp[j][k - 1] : 1) % mod * (k + 1 < i ? dp[k + 1][i - 1] : 1) % mod;
			dp[j][i] %= mod;
	}
		
	cout << dp[0][n - 1] << endl;
 
	return 0;
}
