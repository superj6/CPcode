#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200004, maxm = 101;
int n, m;
int a[maxn], f[maxn];
int b[2][2][maxn];
int dp[2][maxm][maxn];

string solve_puzzle(string s, vector<int> c){
	n = s.size(), m = c.size();
	for(int i = 0; i < n; i++) a[i + 2] = (s[i] == '_' ? 0 : s[i] == 'X' ? 1 : 2);
	a[0] = a[1] = a[n + 2] = a[n + 3] = 2;
	
	for(int t = 0; t < 2; t++){
		dp[t][0][0] = dp[t][0][1] = 1;
		for(int i = 2; i <= n + 1; i++){
			for(int j = 0; j < 2; j++){
				b[t][j][i] = a[i] == j;
				b[t][j][i] += b[t][j][i - 1];
			}
			dp[t][0][i] = !b[t][1][i];
			for(int j = 0; j < m; j++){
				if(a[i] != 1){
					dp[t][j + 1][i] |= dp[t][j + 1][i - 1];
				}
				if(a[i] != 0){
					dp[t][j + 1][i] |= (i >= c[j] + 1 && b[t][0][i] - b[t][0][i - c[j]] == 0 &&
						a[i - c[j]] != 1 && a[i + 1] != 1 && dp[t][j][i - c[j] - 1]);
				}
			}
		}
		reverse(a, a + n + 4);
		reverse(c.begin(), c.end());
	}
	for(int i = 0; i <= m; i++) reverse(dp[1][i], dp[1][i] + n + 4);
	for(int i = 0; i < 2; i++) reverse(b[1][i], b[1][i] + n + 4);
	
	string ret(n, '.');
	for(int i = 2; i <= n + 1; i++){
		if(a[i] == 1) continue;
		for(int j = 0; j <= m; j++){
			if(dp[0][j][i - 1] && dp[1][m - j][i + 1]){
				ret[i - 2] = '_';
				break;
			} 
		}
	}
	for(int i = 2; i <= n + 1; i++){
		for(int j = 0; j < m; j++){
			if(i + c[j] <= n + 2 && b[0][0][i + c[j] - 1] - b[0][0][i - 1] == 0 &&
			a[i - 1] != 1 && a[i + c[j]] != 1 && dp[0][j][i - 2] && dp[1][m - j - 1][i + c[j] + 1]){
				f[i]++, f[i + c[j]]--;
			}
		}
		f[i] += f[i - 1];
		if(f[i]) ret[i - 2] = (ret[i - 2] == '_' ? '?' : 'X');
	}
	
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	string s;
	vector<int> c;
	
	cin >> n >> m;
	cin >> s;
	c.resize(m);
	for(int i = 0; i < m; i++) cin >> c[i];
	
	cout << solve_puzzle(s, c) << endl;

	return 0;
}