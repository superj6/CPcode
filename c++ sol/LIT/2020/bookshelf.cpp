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

const int mod = 1000000007;
const int mxn = 2001;
int n, m, k;
pi a[mxn];
ll dp[mxn][2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].f;
		a[i].s = 0;
	}
	for(int i = 0; i < m; i++){
		cin >> a[n + i].f;
		a[n + i].s = 1;
	}
	
	sort(a, a + n + m);
	
	dp[0][0] = dp[0][1] = 1;
	for(int i = 0; i < n + m; i++){
		if(i == n + m - 1 || a[i].f != a[i + 1].f){
			for(int j = k - a[i].f; j >= 0; j--){
				(dp[j + a[i].f][a[i].s] += dp[j][!a[i].s]) %= mod;
			}
		}else{
			for(int j = k; ~j; j--){
				for(int l = 0; l < 2; l++)
				for(int p = 0; p < 2; p++){
					if(j + (p + 1) * a[i].f <= k){
						(dp[j + (p + 1) * a[i].f][l ^ p] += dp[j][!l]) %= mod;
					} 
				}
			}
			i++;
		}
	}
	
	cout << ((dp[k][0] + dp[k][1]) % mod) << endl;
	
	return 0;
}