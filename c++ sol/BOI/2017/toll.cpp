#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int inf = 0x3f3f3f3f;
const int maxn = 50000, maxk = 5, w = 16;
int n, m, k, q;
int dp[maxk], dp2[maxk];
int st[w][maxn][maxk][maxk];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> k >> n >> m >> q;
	n = (n + k - 1) / k;
	
	memset(st, inf, sizeof(st));
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v >> st[0][u / k][u % k][v % k];
	}
	
	for(int i = 1; i < w; i++)
	for(int j = 0; j + (1 << i) < n; j++)
	for(int f1 = 0; f1 < k; f1++)
	for(int f2 = 0; f2 < k; f2++)
	for(int f3 = 0; f3 < k; f3++){
		st[i][j][f1][f3] = min(st[i][j][f1][f3], st[i - 1][j][f1][f2] + st[i - 1][j + (1 << (i - 1))][f2][f3]);
	}
	
	for(int i = 0; i < q; i++){
		int u, v;
		cin >> u >> v;
		memset(dp, inf, sizeof(dp));
		dp[u % k] = 0;
		u /= k;
		for(int j = w - 1; j >= 0; j--){
			if(u + (1 << j) <= v / k){
				memset(dp2, inf, sizeof(dp2));
				for(int f1 = 0; f1 < k; f1++)
				for(int f2 = 0; f2 < k; f2++){
					dp2[f2] = min(dp2[f2], dp[f1] + st[j][u][f1][f2]);
				}
				u += (1 << j);
				memcpy(dp, dp2, sizeof(dp));
			}
		}
		cout << (dp[v % k] == inf ? -1 : dp[v % k]) << endl;
	}

	return 0;
}