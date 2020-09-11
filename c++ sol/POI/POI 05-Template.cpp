/*
	The best substring will obviously be both a prefix and suffix, so we can use that to our advantage to use prefix function
for dp transitions. For each prefix to index i, hold p[i] = prefix function, dp[i] = shortest template and f[i] = largest prefix of
string that can be covered with prefix dp[i] so far. If a shorter prefix than i can be used, it will be the value x = dp[p[i] - 1], 
since f[x] will be at least as far forward as f[p[i] - 1] as it is a suffix of p[i] - 1 so it will appear in at least every position
of p[i] - 1, and it is a better answer. This means you can just test if f[x] < i - x - 1. If it is, that value won't work, so set
dp[i] = f[i] = i since only using the whole prefix is a valid answer. Otherwise, dp[i] = x and the new value of f[x] = i.
*/

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
