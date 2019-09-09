#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	string a, b;
	cin >> a >> b;
	
	int dp[a.size() + 1][b.size() + 1];
	
	for(int i = 0; i <= a.size(); i++){
		for(int j = 0; j <= b.size(); j++){
			if(i == 0 || j == 0){
				dp[i][j] = i != 0 ? i : j;
				continue;
			}
			
			dp[i][j] = min(dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]), min(dp[i - 1][j], dp[i][j - 1]) + 1);
		}
	}
	
	cout << dp[a.size()][b.size()] << endl;

	return 0;
}