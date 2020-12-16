#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
const int maxn = 500002;
int n;
long long a[maxn], dp[maxn], it[maxn];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		a[i] += a[i] + a[i - 1];
	}
	
	for(int i = 1; i <= n; i++){
		it[i] = max(it[i], it[i - 1]);
		dp[i] = dp[it[i]] + 1;
		it[lower_bound(a, a + n + 1, 2 * a[i] - a[it[i]]) - a] = i;
	}
	
	cout << dp[n] << endl;
 
	return 0;
}
