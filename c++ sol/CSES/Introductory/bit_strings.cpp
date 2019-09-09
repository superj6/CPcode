#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const long long mod = 1000000007;

long long modpow(long long b, int e){
	long long ans = 1;
	for(; e > 0; e >>= 1){
		if(e & 1) ans = (ans * b) % mod;
		b = (b * b) % mod;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	cout << modpow(2, n) << endl;

	return 0;
}