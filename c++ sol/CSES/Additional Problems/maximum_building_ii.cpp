#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define pii pair<pi, pi>
 
const int maxn = 1001;
int n, m;
int a[maxn];
int dp[maxn][maxn];
stack<int> stk;
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= m; j++){
			if(j < m){
				char c;
				cin >> c;
				a[j] = (c == '.') * (1 + a[j]);
			}
			while(!stk.empty() && a[j] < a[stk.top()]){
				int c = stk.top();
				stk.pop();
				if(a[c]) dp[a[c] - 1][j - (stk.empty() ? -1 : stk.top()) - 2]++;
			}
			stk.push(j);
		}
		while(!stk.empty()) stk.pop();
	}
	
	for(int i = n - 1; i >= 0; i--)
	for(int j = m - 1; j >= 0; j--){
		dp[i][j] += dp[i + 1][j];
		dp[i][j] += dp[i][j + 1];
		dp[i][j] -= dp[i + 1][j + 1];
	}
	for(int i = 1; i < n; i++)
	for(int j = 1; j < m; j++){
		dp[0][j] += dp[i][j];
		dp[i][j] += dp[i][j + 1];
	}
	
	for(int i = 0; i < n; i++){
		cout << dp[i][0];
		for(int j = 1; j < m; j++) cout << " " << dp[i][j];
		cout << endl;
	}
	
	return 0;
}