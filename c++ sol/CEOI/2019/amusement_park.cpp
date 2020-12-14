#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mod = 998244353;
const int maxn = 18;
int n, m;
int d[maxn];
map<int, int> dp[1 << maxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		d[u] |= 1 << v;
		d[v] |= 1 << u;
	}
	
	dp[0][(1 << n) - 1] = 1;
	for(int i = 0; i < (1 << n) - 1; i++)
	for(auto it : dp[i]){
		int c = it.f;
		for(int j = 0; j < n; j++){
			if(c & (1 << j)){
				c ^= (1 << j);
				(dp[i | (1 << j)][(c | d[j]) & (((1 << n) - 1) ^ i)] += it.s) %= mod;
			}
		}
	}
	
	cout << ((ll)dp[(1 << n) - 1][0] * m % mod * (mod + 1) / 2 % mod) << endl;

	return 0;
}