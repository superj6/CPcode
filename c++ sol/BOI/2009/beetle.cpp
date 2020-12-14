#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 302;
int n, m;
vector<int> a[2];
int dp[mxn][mxn][2];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		a[x < 0].push_back(abs(x));
	}
	
	for(int i = 0; i < 2; i++){
		a[i].push_back(0);
		sort(a[i].begin(), a[i].end());
	} 
	
	int ret = 0;
	for(int t = 0; t <= n; t++){
		memset(dp, 0x3f, sizeof(dp));
		for(int i = 0; i < 2; i++) dp[0][0][i] = 0;
		for(int i = 0; i < a[0].size(); i++)
		for(int j = 0; j < a[1].size(); j++){
			int x = t - i - j;
			if(!x){
				for(int k = 0; k < 2; k++){
					ret = max(ret, t * m - dp[i][j][k]);
				}
			}else if(x > 0){
				dp[i + 1][j][0] = min({
					dp[i + 1][j][0], 
					dp[i][j][0] + x * (a[0][i + 1] - a[0][i]), 
					dp[i][j][1] + x * (a[0][i + 1] + a[1][j])
				});
				dp[i][j + 1][1] = min({
					dp[i + 1][j][1], 
					dp[i][j][1] + x * (a[1][j + 1] - a[1][j]), 
					dp[i][j][0] + x * (a[0][i] + a[1][j + 1])
				});
			}
		}
	}
	
	cout << ret << endl;

	return 0;
}