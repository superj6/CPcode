#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	freopen("cbarn2.in", "r", stdin);
	freopen("cbarn2.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	long long a[n];
	for(int i = 0; i < n; i++) cin >> a[i];
	
	long long minv = 100000000000007;
	int p;
	long long sum[n];
	long long dp[n][k];
	
	for(int st = 0; st < n; st++){
		//cout << st << endl;
		for(int j = 0; j < k; j++){
			p = st;
			sum[st] = 0;
			dp[st][j] = 0;
			for(int i = st + 1; i < st + n; i++){
				p = st;
				if(j == 0){
					dp[i % n][j] = dp[(i + n - 1) % n][j] + (i - st) * a[i % n];
					sum[i % n] = sum[(i + n - 1) % n] + a[i % n];
				}else{
					long long cur = 10000000007;
					for(int p = st; p < i - 1; p++) cur = min(cur, dp[p % n][j - 1] + ((dp[i % n][0] - dp[p % n][0]) - (p + 1 - st) * (sum[i % n] - sum[p % n])));
					
					dp[i % n][j] = cur;
				}
				//if(j == 1) cout << dp[i % n][j] << " ";
			}
			//if(j == 1) cout << endl;
		}
		minv = min(minv, dp[(st + n - 1) % n][k - 1]);
	}
	
	cout << minv << endl;

	return 0;
}