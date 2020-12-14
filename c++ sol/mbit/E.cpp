#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1001;
int n, k;
ll a[2][mxn], f[mxn];
ll dp[2][mxn][mxn];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	k++;
	
	for(int i = 1; i <= n; i++){
		cin >> a[0][i];
		a[1][i] = (k - a[0][i]) % k, f[i] = 0x3f3f3f3f3f3f3f3f;
		for(int t = 0; t < 2; t++)
		for(ll j = i, x = i, s = 0; j; j--){
			if(a[t][j] > a[t][x]){
				dp[t][j][i] = s + dp[t][j][x - 1];
			}else if(a[t][j] < a[t][x]){
				x = j;
				dp[t][j][i] = a[t][x] + (s = dp[t][j + 1][i] - a[t][x]);
			}else{
				if(j + 1 < x) s += dp[t][j + 1][x - 1] - a[t][x];
				x = j;
				dp[t][j][i] = a[t][x] + s;
			}
			f[i] = min(f[i], dp[t][j][i] + f[j - 1]);
		}
	}
	
	cout << f[n] << endl;

	return 0;
}