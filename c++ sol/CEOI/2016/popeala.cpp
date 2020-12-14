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

const int maxn = 20001, maxm = 51;
int n, m, k;
int p[maxn], b[maxn];
int a[maxn][maxm];
int dp[maxm][maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> m >> n >> k;
	
	for(int i = 1; i <= n; i++){
		cin >> p[i];
		p[i] += p[i - 1];
	} 
	
	for(int j = 0; j < m; j++)
	for(int i = 1; i <= n; i++){
		char c;
		cin >> c;
		a[i][j] = c & 1 ? a[i - 1][j] : i;
	} 
	
	for(int i = 1; i <= n; i++){
		sort(a[i], a[i] + m);
		a[i][m] = i;
	}
	
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int t = 1; t <= k; t++){
		memset(b, 0x3f, sizeof(b));
		for(int i = 1; i <= n; i++){
			for(int j = 0; j <= m; j++){
				for(int l = a[i - 1][j]; l < a[i][j]; l++){
					b[j] = min(b[j], dp[t - 1][l] - p[l] * j);
				}
				if(a[i][j]){
					dp[t][i] = min(dp[t][i], b[j] + p[i] * j);
				}
			}
		}
		cout << dp[t][n] << endl;
	}

	return 0;
}