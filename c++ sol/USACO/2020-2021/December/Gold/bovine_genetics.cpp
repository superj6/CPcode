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
const int mxn = 100000, k = 4;
const char c[k] = {'A', 'G', 'C', 'T'};
int n;
string s;
int a[mxn];
int dp[mxn][k][k][k];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	n = s.size();
	
	for(int i = 0; i < n; i++) a[i] = find(c, c + k, s[i]) - c;
	
	for(int i = 0; i < k; i++) if(a[0] == k || a[0] == i)
	for(int j = 0; j < k; j++){
		dp[0][i][i][j] = 1;
	}
	
	for(int i = 1; i < n; i++)
	for(int j = 0; j < k; j++) if(a[i] == k || a[i] == j)
	for(int l = 0; l < k; l++)
	for(int jj = 0; jj < k; jj++){
		(dp[i][j][j][l] += dp[i - 1][jj][l][jj]) %= mod;
		if(j != jj) for(int p = 0; p < k; p++){
			(dp[i][j][l][p] += dp[i - 1][jj][l][p]) %= mod;
		}
	}
	
	int ret = 0;
	for(int i = 0; i < k; i++)
	for(int j = 0; j < k; j++){
		(ret += dp[n - 1][i][j][i]) %= mod;
	} 
	
	cout << ret << endl;

	return 0;
}