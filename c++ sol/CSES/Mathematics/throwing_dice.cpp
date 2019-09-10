#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
 
const int mod = 1e9 + 7;
 
long long m[6][6] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0}
};
 
long long f[6][6] = {
	{1, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 1}
};
 
void mult(long long a[6][6], long long b[6][6]){
	long long ret[6][6];
	memset(ret, 0, sizeof(ret));
	for(int i = 0; i < 6; i++)
	for(int j = 0; j < 6; j++)
	for(int k = 0; k < 6; k++){
		ret[i][j] += (a[i][k] * b[k][j]) % mod;
		ret[i][j] %= mod;
	}
	
	for(int i = 0; i < 6; i++)
	for(int j = 0; j < 6; j++){
		a[i][j] = ret[i][j];
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	long long n;
	cin >> n;
	
	for(; n > 0; n >>= 1){
		if(n & 1) mult(f, m);
		mult(m, m);
	}
	
	cout << f[0][0] << endl;
 
	return 0;
}