#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const long long mod = 1000000007;

long long modpow(long long b, int e){
	long long ret = 1;
	for(int i = 0; (1 << i) <= e; i++){
		if((1 << i) & e) ret = (ret * b) % mod;
		b = (b * b) % mod;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		cout << modpow(a, b) << endl;
	}

	return 0;
}