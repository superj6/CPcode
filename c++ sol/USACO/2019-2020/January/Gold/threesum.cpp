#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 5000, maxv = 2000001;
int n, q;
int a[maxn], used[2 * maxv];
long long dp[maxn][maxn];

int main(){
	freopen("threesum.in", "r", stdin);
	freopen("threesum.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		for(int j = i - 1; j >= 0; j--){
			dp[j][i] = used[-a[i] - a[j] + maxv] + dp[j + 1][i] + dp[j][i - 1] - dp[j + 1][i - 1];
			used[a[j] + maxv]++;
		}
		for(int j = 0; j < i; j++) used[a[j] + maxv]--;
	}
	
	for(int i = 0; i < q; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		cout << dp[x][y] << endl;
	}
	
	return 0;
}