#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
const int maxn = 100, maxm = 100001;
int n, m;
int x[maxn], y[maxn], z[maxn];
int dp[maxm];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++) cin >> x[i];
	for(int i = 0; i < n; i++) cin >> y[i];
	for(int i = 0; i < n; i++) cin >> z[i];
	
	for(int i = 0; i < n; i++){
		for(int k = 0; z[i]; k++){
			int l = min(z[i], (1 << k));
			for(int j = m - x[i] * l; j >= 0; j--){
				dp[j + x[i] * l] = max(dp[j + x[i] * l], dp[j] + y[i] * l);
			}
			z[i] -= l;
		}
	}
	for(int j = 1; j <= m; j++) dp[j] = max(dp[j], dp[j - 1]);
	
	cout << dp[m] << endl;
 
	return 0;
}