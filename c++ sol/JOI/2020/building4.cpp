//VwzqYy37
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 4000;
int n;
int a[maxn], b[maxn];
bool dp[maxn][maxn][2];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < 2 * n; i++) cin >> a[i];
	for(int i = 0; i < 2 * n; i++) cin >> b[i];
	
	dp[0][1][0] = dp[0][0][1] = 1;
	for(int i = 1; i < 2 * n; i++)
	for(int j = 0; j <= n; j++){
		if(j) dp[i][j][0] = ((a[i - 1] <= a[i] && dp[i - 1][j - 1][0]) || (b[i - 1] <= a[i] && dp[i - 1][j - 1][1]));
		dp[i][j][1] = ((a[i - 1] <= b[i] && dp[i - 1][j][0]) || (b[i - 1] <= b[i] && dp[i - 1][j][1]));
		//if(dp[i][j][0]) cout << i << " " << j << " " << 0 << endl;
		//if(dp[i][j][1]) cout << i << " " << j << " " << 1 << endl;
		
	}
	
	if(!dp[2 * n - 1][n][0] && !dp[2 * n - 1][n][1]){
		cout << -1 << endl;
		return 0;
	}
	
	string ret;
	for(int i = 2 * n - 1, j = n; i >= 0; i--){
		if(!dp[i][j][1]){
			ret += 'A';
			j--;
		}else if(!dp[i][j][0]){
			ret += 'B';
		}else if(a[i] < b[i]){
			ret += 'A';
			j--;
		}else{
			ret += 'B';
		}
	}
	reverse(ret.begin(), ret.end());
	
	cout << ret << endl;

	return 0;
}