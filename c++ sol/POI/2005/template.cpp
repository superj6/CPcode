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

const int mxn = 500001;
int n;
string s;
int p[mxn], f[mxn], dp[mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s;
	n = s.size();
	
	for(int i = 1, j = 0, x; i < n; i++){
		while(j && s[i] != s[j]) j = p[j - 1];
		p[i] = (j += s[i] == s[j]);
		
		if(!p[i] || f[x = dp[p[i] - 1]] < i - x - 1) dp[i] = f[i] = i;
		else dp[i] = x, f[x] = i;
	}
	
	cout << dp[n - 1] + 1 << endl;

	return 0;
}