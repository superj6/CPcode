#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second
 
const int maxn = 1001;
int n, m;
int a[maxn];
int dp[maxn][maxn];
stack<pi> stk;
 
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
			int cnt = 1;
			while(!stk.empty() && a[j] <= a[stk.top().f]){
				pi p = stk.top();
				stk.pop();
				cnt += p.s;
				if(a[p.f]) dp[a[p.f] - 1][j - p.f + p.s - 1]--;
				if(!stk.empty() && a[stk.top().f]) dp[a[stk.top().f] - 1][j - p.f + p.s - 1]++;
			}
			if(a[j]) dp[a[j] - 1][cnt - 1]++;
			if(!stk.empty() && a[stk.top().f]) dp[a[stk.top().f] - 1][cnt - 1]--;
			stk.push({j, cnt});
		}
		while(!stk.empty()) stk.pop();
	}
	
	for(int i = n - 2; i >= 0; i--)
	for(int j = 0; j < m; j++){
		dp[i][j] += dp[i + 1][j];
	}
	
	for(int i = 0; i < n; i++)
	for(int j = 1; j < m; j++){
		dp[i][j] += dp[i][j - 1];
	}
	
	for(int i = 0; i < n; i++)
	for(int j = m - 2; j >= 0; j--){
		dp[i][j] += dp[i][j + 1];
	}
	
	for(int i = 0; i < n; i++){
		cout << dp[i][0];
		for(int j = 1; j < m; j++) cout << " " << dp[i][j];
		cout << endl;
	}
	
	return 0;
}