#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000, mxk = 40;
int n, m, k;
int a[mxn], b[mxn], d[mxn];
ll f[mxk], ff[mxk], dp[mxk], ans[mxk];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m;
	
	for(int i = 0; i < n; i++){
		char c;
		cin >> a[i] >> b[i] >> c;
		if(d[i] = (c == 'D')) ans[b[i]] += 2 * (m - a[i]);
	}
	
	for(int i = n - 1; ~i; i--){
		if(d[i]){
			for(int j = 0; j < k; j++){
				ans[j] += (m - a[i]) * f[j] - a[i] * ff[j];
				f[j] += ff[j], ff[j] = 0;
			}
			rotate(f, f + (k - b[i]) % k, f + k);
			rotate(dp, dp + (k - b[i]) % k, dp + k);
			m = a[i];
		}else{
			ans[b[i]] += a[i];
			ff[b[i]]++, dp[b[i]] += a[i];
		}
	}
	
	for(int i = 0; i < k; i++){
		ans[i] += m * f[i] + dp[i];
		cout << (ans[i] / 2) << "." << (5 * (ans[i] & 1)) << endl;
	} 

	return 0;
}