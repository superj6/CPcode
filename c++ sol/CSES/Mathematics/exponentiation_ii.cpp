#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1000000007;

long long modpow(long long b, int e, int m){
	long long ret = 1;
	for(int i = 0; (1 << i) <= e; i++){
		if((1 << i) & e) ret = (ret * b) % m;
		b = (b * b) % m;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int a, b, c;
		cin >> a >> b >> c;
		cout << modpow(a, modpow(b, c, mod - 1), mod) << endl;
	}

	return 0;
}