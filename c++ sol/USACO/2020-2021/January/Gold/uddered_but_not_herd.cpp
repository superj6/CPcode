#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxm = 20, k = 26;
int n, m;
string s;
int a[k];
int f[mxm][mxm];
int dp[1 << mxm];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	n = s.size();
	
	memset(a, -1, sizeof(a));
	for(int i = 0; i < n; i++){
		if(!~a[s[i] -= 'a']) a[s[i]] = m++; 
		s[i] = a[s[i]];
		if(i) f[s[i - 1]][s[i]]++;
	}
	
	dp[0] = 1;
	for(int i = 1; i < (1 << m); i++){
		dp[i] = n;
		for(int j = 0; j < m; j++) if((i >> j) & 1){
			int x = 0;
			for(int l = 0; l < m; l++) x += ((i >> l) & 1) * f[j][l];
			dp[i] = min(dp[i], dp[i ^ (1 << j)] + x);
		}
	}
	
	cout << dp[(1 << m) - 1] << endl;
	
	return 0;
}