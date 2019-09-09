#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 1e6 + 1, mod = 1e9 + 7;
long long f[maxn];

void gen(){
	f[0] = 1;
	f[1] = 0;
	
	for(int i = 2; i < maxn; i++) f[i] = ((i - 1) * (f[i - 1] + f[i - 2])) % mod;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	gen();
	
	int n;
	cin >> n;
	
	cout << f[n] << endl;

	return 0;
}