#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1000;
long long r, c;
long long dp[maxn][maxn], minv[maxn][maxn];
long long ret;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> r >> c;
	
	for(long long i = 0; i < r; i++){
		for(long long j = 0; j < c; j++){
			cin >> minv[i][j];
			if(i) minv[i][j] = min(minv[i][j], minv[i - 1][j]);
			if(j) minv[i][j] = min(minv[i][j], minv[i][j - 1]);
			
			dp[i][j] = minv[i][j] * (i + 1) * (j + 1);
			if(i) dp[i][j] = max(dp[i][j], dp[i - 1][j] + minv[i][j] * (j + 1));
			if(j) dp[i][j] = max(dp[i][j], dp[i][j - 1] + minv[i][j] * (i + 1));
			
			ret = max(ret, dp[i][j]);
		}
	}
	
	cout << ret << endl;

	return 0;
}