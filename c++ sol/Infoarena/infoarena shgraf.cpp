/*
	This problem is mostly about knowing Cayley's generalized formula for number of forrests with k components.
The formula is T(n, k) = k * n^(n - k - 1), where n is the number of labeled nodes, k is the number of forrests,
and the nodes 1, 2, ..., k are each in different components. You can find this on wikipedia. After knowing this
formula, it is just a matter that a connected shgraf is just a cycle with a tree off each node, which you can
think of as different connected components connected by a cycle, so you can just math the number of ways to arrange
the nodes of the tree in the cycle, then use dp to combine different connected components. The time complexity is
O(n^2). 
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 30011;
const int mxn = 251;
int n, k;
int f[mxn], ff[mxn], dp[mxn];
int c[mxn][mxn], p[mxn][mxn];

int main(){
	freopen("shgraf.in", "r", stdin);
	freopen("shgraf.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i <= n; i++){
		f[i] = i ? i * f[i - 1] % mod : 1;
		c[i][0] = p[i][0] = 1;
		for(int j = 1; j <= i; j++) p[i][j] = i * p[i][j - 1] % mod;
		for(int j = 1; j <= i; j++){
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
			(ff[i] += (j >= k) * (mod + 1) / 2 * f[j - 1] % mod * c[i][j] % mod * 
				(i == j ? 1 : j * p[i][i - j - 1] % mod)) %= mod;
		}
	}
	
	dp[0] = 1;
	for(int i = k; i <= n; i++)
	for(int j = k; j <= i; j++){
		(dp[i] += c[n + j - i - 1][j - 1] * ff[j] % mod * dp[i - j]) %= mod;
	}
	
	cout << dp[n] << endl;
	
	return 0;
}