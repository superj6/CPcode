#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 1000000007;
const int mxn = 60, mxk = 5;
int n, k, q;
int g[mxn][mxn], f[mxn][mxk];
int dp[mxn][1 << mxk], dp2[mxn][1 << mxk];
vector<int> gr[1 << mxk];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> q;

	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		g[i][j] = c & 1;
	}
	
	for(int i = 0; i < (1 << k); i++)
	for(int j = 0; j < k; j++) if(!((i >> j) & 1)){
		gr[i].push_back((i ^ (i & ((1 << j) - 1))) | (1 << j));
	}
	
	int xx = -1, ss = -1;
	while(q--){
		int x, s, y, t;
		cin >> x >> s >> y >> t;
		x--, s--, y--, t--;

		if(x != xx || s != ss){
			memset(f, 0, sizeof(f));
			f[ss = s][xx = x] = 1;
			memset(dp, 0, sizeof(dp));
			dp[s][1 << x] = 1;
			for(int l = 0; l < (1 << k); l++){
				swap(dp, dp2);
				memset(dp, 0, sizeof(dp));
				for(int i = 0; i < n; i++)
				for(int ii = 0; ii < n; ii++) if(g[i][ii])
				for(int j = 0; j < (1 << k); j++)
				for(int jj : gr[j]){
					(dp[ii][jj] += dp2[i][j]) %= mod;
					int x = (j ^ jj) & jj;
					(f[ii][__lg(x & -x)] += dp2[i][j]) %= mod;
				}
			}	
		}
		
		cout << f[t][y] << endl;
	}

	return 0;
}