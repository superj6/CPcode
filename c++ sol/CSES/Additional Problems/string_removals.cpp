#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long mod = 1000000007;
const int maxn = 5000001;
int n;
string s;
long long dp[maxn], prv[26];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	n = s.size();
	
	dp[0] = 1;
	memset(prv, -1, sizeof(prv));
	for(int i = 0; i < n; i++){
		int c = s[i] - 'a';
		dp[i + 1] = (mod + 2 * dp[i] - (prv[c] == -1 ? 0 : dp[prv[c]])) % mod;
		prv[c] = i;
	}
	
	cout << ((mod + dp[n] - 1) % mod) << endl;

	return 0;
}