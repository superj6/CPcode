#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

typedef __uint128_t u128;

const u128 mod = 1e9 + 7;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long n;
	cin >> n;
	
	long long ret = 0;
	for(u128 i = 1; i <= sqrt(n); i++){
		ret = (ret + (i * (n / i)) % mod) % mod;
		
		//cout << i << endl;
		
		if(n / i != i){
			//cout << n / (i + 1) << " " << n / i << endl;
			ret = (ret + (i * (((n / i) * (n / i + 1) / 2) % mod)) % mod) % mod;
			ret = (mod + ret - (i * (((n / (i + 1)) * (n / (i + 1) + 1) / 2) % mod)) % mod) % mod;
		}
	}
	
	cout << ret << endl;

	return 0;
}