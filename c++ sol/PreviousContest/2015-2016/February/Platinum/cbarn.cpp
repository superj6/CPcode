#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int maxn = 1000, maxk = 7;
const long long inf = 10000000000007;
int n, k;
long long sum[maxn];
long long dp[maxn][maxk];

void solve(int l, int r, int lo, int hi, int j, int st){
	if(l == r) return;
	int i = (l + r) / 2;
	
	int bestp = -1;
	long long best = inf; 
	for(int p = lo; p < min(hi, i); p++){
		if(best > dp[p % n][j - 1] + ((dp[i % n][0] - dp[p % n][0]) - (p + 1 - st) * (sum[i % n] - sum[p % n]))){
			bestp = p;
			best = dp[p % n][j - 1] + ((dp[i % n][0] - dp[p % n][0]) - (p + 1 - st) * (sum[i % n] - sum[p % n]));
		}
	}
	
	dp[i % n][j] = best;
	
	solve(l, i, lo, bestp + 1, j, st);
	solve(i + 1, r, bestp, hi, j, st);
}

int main(){
	freopen("cbarn.in", "r", stdin);
	freopen("cbarn.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	long long a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	long long minv = inf;
	
	for(int st = 0; st < n; st++){
		for(int j = 0; j < k; j++){
			sum[st] = 0;
			dp[st][j] = 0;
			
			if(j == 0){
				for(int i = st + 1; i < st + n; i++){
					dp[i % n][j] = dp[(i + n - 1) % n][j] + (i - st) * a[i % n];
					sum[i % n] = sum[(i + n - 1) % n] + a[i % n];
				}
			}else{
				solve(st + 1, st + n, st, st + n, j, st);
			}
		}
		minv = min(minv, dp[(st + n - 1) % n][k - 1]);
	}
	
	cout << minv << endl;

	return 0;
}