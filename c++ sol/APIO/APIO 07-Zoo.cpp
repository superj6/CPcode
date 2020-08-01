/*
  Because each child is only dependent on five contiguous animals, you can iterate over all possible starting values for the first
five animals, and do dp holding a bitset whether you choose an animal or not. At the end of each dp, then just add the values that
are partially between beginning and end of array since you needed to wait until you decide for all animals in range what you are
going to do before adding. Complexity O(n * 2^(2 * 5)).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <functional>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 10000, k = 5;
int n, m;
int a[mxn][1 << k], dp[mxn][1 << k];
function<int(int, int)> f[2] = {
	[](int x, int y){ return (x & y) != x;},
	[](int x, int y){ return (x & y) > 0;}
};

void answer(){
	cin >> n >> m;
	
	memset(a, 0, sizeof(a));
	for(int i = 0; i < m; i++){
		int x;
		int y[2], c[2] = {0};
		cin >> x >> y[0] >> y[1];
		(x += k - 2) %= n;
		for(int t = 0; t < 3; t++){
			if(t < 2) for(int j = 0; j < y[t]; j++){
				int z;
				cin >> z;
				(z += n - (x - k + 1) - 1) %= n;
				c[t] |= (1 << z);
			}
			for(int j = 0; j < (1 << k); j++){
				int w = 1;
				for(int l = 0; l < 2; l++){
					if(((t + 1) >> l) & 1) w &= f[l](c[l], j);
				} 
				a[x][j] += (2 * (t < 2) - 1) * w;
			} 
		}
	}
	
	int ret = 0;
	for(int t = 0; t < (1 << k); t++){
		memset(dp, 0xcf, sizeof(dp));
		dp[k - 1][t] = a[k - 1][t];
		for(int i = k; i < n; i++)
		for(int j = 0; j < (1 << k); j++)
		for(int l = 0; l < 2; l++){
			int x = (j >> 1) | (l << (k - 1));
			dp[i][x] = max(dp[i][x], dp[i - 1][j] + a[i][x]);
		}
		for(int i = 0; i < (1 << k); i++){
			for(int j = 0; j < k - 1; j++){
				dp[n - 1][i] += a[j][(i >> (j + 1)) | ((t << (k - j - 1)) & ((1 << k) - 1))];
			}
			ret = max(ret, dp[n - 1][i]);
		}
	}
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
