#include <iostream>
#include <cstdio>
#include <algorithm>
#include <array>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
const int mxn = 50000, m = 4;
typedef array<int, m> T;
int n, k;
T a, v;
ll dp[m + 1];
int f[m + 1][m + 1];
map<T, int> mp[m + 1];
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			char c;
			cin >> c;
			a[j] = 1 + (isdigit(c) ? c - '0' : 10 + c - 'a');
		} 
		for(int j = 0; j < (1 << m); j++){
			v = T();
			for(int l = 0; l < m; l++){
				if((j >> l) & 1) v[l] = a[l];
			} 
			mp[__builtin_popcount(j)][v]++;
		}
	}
	
	for(int i = 0; i <= m; i++){
		f[i][0] = 1;
		for(int j = 1; j <= i; j++){
			f[i][j] += f[i - 1][j] + f[i - 1][j - 1];
		} 
	}
	
	for(int i = m; ~i; i--){
		for(auto &j : mp[i]) dp[i] += (ll)j.s * (j.s - 1) / 2;
		for(int j = 0; j < i; j++) dp[j] -= f[i][j] * dp[i];
	}
	
	cout << dp[m - k] << endl;
 
	return 0;
}