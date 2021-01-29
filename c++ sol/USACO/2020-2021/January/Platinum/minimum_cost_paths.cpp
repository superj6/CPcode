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

const int mxn = 2001;
int n, m, q;
ll a[mxn * mxn];
ll dp[mxn][mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	bool t = 1;
	a[0] = 0x3f3f3f3f;
	for(int i = 1; i <= m; i++) cin >> a[i], t &= i <= 2 || a[i - 1] > a[i];
	
	if(!t){
		memset(dp[0], 0x3f, sizeof(dp[0]));
		for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1] + i * (i + a[j] - a[j + 1]));
			//cout << dp[i][j] << (j == m ? endl : ' ');
		}
	}
	
	cin >> q;
	
	while(q--){
		int x, y;
		cin >> x >> y;
		if(t) cout << ((x - 1) * a[y] + y - 1) << endl;
		else cout << (dp[x][y - 1] + x * a[y] - a[1]) << endl;
	}
	
	return 0;
}