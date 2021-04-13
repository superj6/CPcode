#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 152;
int n;
int a[mxn][mxn], f[mxn][mxn]; //grid and closest non-grass
int dp[mxn][mxn][2][2]; //left right point, turning inward or outward

void add(int &x, int y){
	x += y;
	if(x >= mod) x -= mod;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= n; j++){
		char c;
		cin >> c;
		a[i][j] = c == 'G';
		f[i][j] = a[i][j] * (1 + f[i][j - 1]);
	}
	
	//dp row by row, left and right only move right angles outward than inward
	int ret = 0;
	for(int i = 1; i <= n; i++){
		//inward inward
		for(int j = 1; j <= n; j++)
		for(int l = n; l >= j; l--){
			add(dp[j][l][1][1], dp[j - 1][l][1][1]);
			add(dp[j][l][1][1], dp[j][l + 1][1][1]);
			add(dp[j][l][1][1], mod - dp[j - 1][l + 1][1][1]);
			add(dp[j][l][1][1], dp[j - 1][l][0][1]);
			add(dp[j][l][1][1], dp[j][l + 1][1][0]);
			add(dp[j][l][1][1], dp[j - 1][l + 1][0][0]);
		}
		
		//inward outward
		for(int j = 1; j <= n; j++)
		for(int l = j; l <= n; l++){
			add(dp[j][l][1][0], dp[j - 1][l][1][0]);
			add(dp[j][l][1][0], dp[j][l - 1][1][0]);
			add(dp[j][l][1][0], mod - dp[j - 1][l - 1][1][0]);
			add(dp[j][l][1][0], dp[j - 1][l][0][0]);
		}
		
		//outward inward
		for(int j = n; j; j--)
		for(int l = n; l >= j; l--){
			add(dp[j][l][0][1], dp[j + 1][l][0][1]);
			add(dp[j][l][0][1], dp[j][l + 1][0][1]);
			add(dp[j][l][0][1], mod - dp[j + 1][l + 1][0][1]);
			add(dp[j][l][0][1], dp[j][l + 1][0][0]);
		}
		
		//outward outward
		for(int j = n; j; j--)
		for(int l = j; l <= n; l++){
			add(dp[j][l][0][0], dp[j + 1][l][0][0]);
			add(dp[j][l][0][0], dp[j][l - 1][0][0]);
			add(dp[j][l][0][0], mod - dp[j + 1][l - 1][0][0]);
		}
		
		//make sure each range is actually possible, add new starting point, and add to total
		for(int j = 1; j <= n; j++)
		for(int l = j; l <= n; l++)
		for(int x = 0; x < 2; x++)
		for(int y = 0; y < 2; y++){
			add(dp[j][l][x][y], !x && !y);
			dp[j][l][x][y] *= (j > l - f[i][l]);
			add(ret, dp[j][l][x][y]);
		}
	}
	
	cout << ret << endl;
	
	return 0;
}