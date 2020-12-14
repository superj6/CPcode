#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 7501;
int n, m;
int dp[maxn];
long long f[maxn][maxn];
int lcp[maxn];
vector<int> p;

long long modpow(long long b, int e){
	long long ret = 1;
	for(; e; e >>= 1){
		if(e & 1) ret = ret * b % m;
		b = b * b % m;
	}
	return ret;
}

int solve(int x){
	int ret = 0;
	dp[0] = m - 2;
	for(int i = 1; i * x <= n; i++){
		dp[i] = 0;
		for(int j = 1; j <= i; j++){
			dp[i] += m - 1 - (f[i * x - 1][j * x - 1] * dp[i - j]) % (m - 1);
			dp[i] %= m - 1;
		}
		ret += f[n][n - i * x] * dp[i] % (m - 1);
		ret %= m - 1;
	}
	return ret;
}

int main(){
	freopen("exercise.in", "r", stdin);
	freopen("exercise.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i <= n; i++){
		f[i][0] = 1;
		for(int j = 0; j < i; j++) f[i][j + 1] = (f[i][j] * (i - j)) % (m - 1);
	}
	
	long long ret = 1;
	for(int i = 2; i <= n; i++){
		if(!lcp[i]){
			lcp[i] = i;
			p.push_back(i);
			for(int j = i; j <= n; j *= i) ret = ret * modpow(i, solve(j)) % m;
		}
		for(int j = 0; j < p.size() && p[j] <= lcp[i] && i * p[j] <= n; j++){
			lcp[i * p[j]] = p[j];
		}
	}
	
	cout << ret << endl;

	return 0;
}