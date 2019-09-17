#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'

const int maxn = 100;
int n;
int a[maxn];
int dp[maxn][maxn];
double ret;

void precomp(){
	for(int i = 0; i < maxn; i++)
	for(int j = 0; j < maxn; j++){
		if(i + 1 < maxn) dp[i + 1][j] = dp[i][j] + max(j - i - 1, 0);
		if(j + 1 < maxn) dp[i][j + 1] = dp[i][j] + min(i + 1, j + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << setprecision(6) << fixed;
	
	precomp();
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
		for(int j = 0; j < i; j++){
			ret += 1.0 * dp[a[i]][a[j]] / ((a[i] + 1) * (a[j] + 1));
		}
	}
	
	cout << ret << endl;
	
	return 0;
}