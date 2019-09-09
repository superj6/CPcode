#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 2e6 + 1, mod = 1e9 + 7;
long long f[maxn], rf[maxn];
int cnt[26];

void gen(){
	f[0] = rf[0] = 1;
	
	for(int i = 1; i < maxn; i++){
		f[i] = (f[i - 1] * i) % mod;
		rf[i] = 1;
		
		for(long long j = 0, k = f[i]; (1 << j) <= mod - 2; j++){
			if((1 << j) & (mod - 2)) rf[i] = (rf[i] * k) % mod;
			k = (k * k) % mod;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	gen();
	
	int n, m;
	cin >> n >> m;
	
	cout << ((f[n + m - 1] * ((rf[n - 1] * rf[m]) % mod)) % mod) << endl;

	return 0;
}