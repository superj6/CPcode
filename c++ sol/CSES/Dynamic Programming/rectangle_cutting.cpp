#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int a, b;
	cin >> a >> b;
	
	int dp[a][b];
	
	for(int i = 0; i < a; i++){
		for(int j = 0; j < b; j++){
			if(i == j){
				dp[i][j] = 0;
				continue;
			}
			
			dp[i][j] = 1000000007;
			
			for(int k = 0; k < i; k++){
				dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k - 1][j] + 1);
			}
			
			for(int k = 0; k < j; k++){
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k - 1] + 1);
			}
		}
	}
	
	cout << dp[a - 1][b - 1] << endl;

	return 0;
}