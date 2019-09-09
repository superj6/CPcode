#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int mod = 1000000007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int a[n + 6];
	memset(a, 0, sizeof(a));
	
	a[0] = 1;
	
	for(int i = 0; i < n; i++){
		for(int j = 1; j <= 6; j++){
 			a[i + j] += a[i];
			a[i + j] %= mod;
		}
	}
	
	cout << a[n] << endl;

	return 0;
}