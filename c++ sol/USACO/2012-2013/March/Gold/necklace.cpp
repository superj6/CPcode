#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxm = 1000;
int n, m;
string s, t;
int dp[maxm], dp2[maxm];
int nx[maxm][26];

int main(){
	freopen("necklace.in", "r", stdin);
	freopen("necklace.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s >> t;
	n = s.size(), m = t.size();
	
	for(int i = 0; i < n; i++) s[i] -= 'a';
	for(int i = 0; i < m; i++) t[i] -= 'a';
	
	for(int i = 1; i < m; i++){
		dp[i] = dp2[i] = -n;
		int p = nx[i - 1][t[i - 1]];
		nx[i - 1][t[i - 1]] = i;
		memcpy(nx[i], nx[p], sizeof(nx[p]));
	}
	nx[m - 1][t[m - 1]] = m;
	
	int ret = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			int c = nx[j][s[i]];
			if(c < m){
				dp[c] = max(dp[c], dp2[j] + 1);
				ret = max(ret, dp[c]);
			}
		}
		memcpy(dp2, dp, sizeof(dp));
	}
	ret = n - ret;
	
	cout << ret << endl;

	return 0;
}
