#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int maxn = 1001;
int dp[maxn][maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++){
		char temp[n];
		cin >> temp;
		for(int j = 1; j <= n; j++){
			dp[i][j] = (temp[j - 1] == '*') + dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1];
		}
	}
	
	for(int i = 0; i < q; i++){
		int y, x, Y, X;
		cin >> y >> x >> Y >> X;
		cout << (dp[Y][X] - dp[y - 1][X] - dp[Y][x - 1] + dp[y - 1][x - 1]) << endl;
	}

	return 0;
}