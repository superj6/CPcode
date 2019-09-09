/*
This is code of SuperJ6 for Codeforces.
Don't copy my code during f*kin' contests.

2.71828182845904523536
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int mod = 1e9 + 7;

long long m[2][2] = {
	{1, 1},
	{1, 0}
};

long long f[2][2] = {
	{1, 1},
	{1, 0}
};

void mult(long long a[2][2], long long b[2][2]){
	long long ret[2][2];
	memset(ret, 0, sizeof(ret));
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < 2; j++)
	for(int k = 0; k < 2; k++){
		ret[i][j] += (a[i][k] * b[k][j]) % mod;
		ret[i][j] %= mod;
	}
	
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < 2; j++){
		a[i][j] = ret[i][j];
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long n;
	cin >> n;
	
	if(n < 2){
		cout << n << endl;
		return 0;
	}
	
	n -= 2;
	
	for(; n > 0; n >>= 1){
		if(n & 1) mult(f, m);
		mult(m, m);
	}
	
	cout << f[0][0] << endl;

	return 0;
}