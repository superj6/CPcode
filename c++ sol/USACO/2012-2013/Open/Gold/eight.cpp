#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 300;
int n;
int a[maxn][maxn];
int dp[2][2][maxn][maxn];

int main(){
	freopen("eight.in", "r", stdin);
	freopen("eight.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		a[i][j] = (c == '.') * ((j ? a[i][j - 1] : 0) + 1);
	}
	
	int ret = 0;
	for(int i = 2; i < n; i++)
	for(int j = 0; j + i < n; j++){
		for(int t = 0; t < 2; t++)
		for(int k = t * (n - 1), l = -1; ~k && k < n; k += 1 - 2 * t){
			if(!a[k][j] || !a[k][i + j]) l = -1;
			if(a[k][i + j] > i){
				if(!~l) l = k;
				dp[i & 1][t][k][j] = (l != k) * 
					(i - 1) * ((1 - 2 * t) * (k - l) - 1);
			}else{
				dp[i & 1][t][k][j] = 0;
			}
		}
		for(int k = 0; k < n; k++){
			dp[i & 1][0][k][j] = max({
				dp[i & 1][0][k][j],
				dp[(i & 1) ^ 1][0][k][j],
				dp[(i & 1) ^ 1][0][k][j + 1]
			});
			ret = max(ret, dp[i & 1][0][k][j] * dp[i & 1][1][k][j]);
		}
	}
	
	cout << (ret - !ret) << endl;

	return 0;
}