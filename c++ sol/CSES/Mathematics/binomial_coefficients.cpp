#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1e6 + 1, mod = 1e9 + 7;
long long f[maxn], rf[maxn];

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
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		cout << ((f[a] * ((rf[b] * rf[a - b]) % mod)) % mod) << endl;
	}

	return 0;
}