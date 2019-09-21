#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const long long mod = 1000000007;
 
long long modpow(long long b, int e){
	long long ret = 1;
	for(; e; e >>= 1){
		if(e & 1) ret = (ret * b) % mod;
		b = (b * b) % mod;
	}
	return ret;
}

const int maxn = 1000001, maxm = 101;
int n, m;
string s;
int r[maxm];
int dp[maxn][maxm], f[maxm][26];

void precomp(){
	r[0] = -1
	for(int i = 1, j = 0; i < m; i++){
		while(j > 0 && s[i] != s[j]) j = r[j - 1];
		j += (s[i] == s[j]);
		r[i + 1] = j;
	}
	
	for(int i = 0; i < m; i++){
		for(int j = i; j > 0; j = r[j - 1]){
			if(!f[i][s[j] - 'A']) f[i][s[j] - 'A'] = j + 1;
		}
		if(!f[i][s[0] - 'A']) f[i][s[0] - 'A'] = 1;
	}
	
	dp[0][0] = 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> s;
	m = s.size();
	
	precomp();
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			for(int k = 0; k < 26; k++){
				dp[i + 1][f[j][k]] += dp[i][j];
				dp[i + 1][f[j][k]] %= mod;
			}
		}
	}
	
	long long ret = 0;
	for(int i = 0; i < m; i++) ret = (ret + dp[n][i]) % mod;
	
	cout << (modpow(26, n) - ret + mod) % mod << endl;

	return 0;
}