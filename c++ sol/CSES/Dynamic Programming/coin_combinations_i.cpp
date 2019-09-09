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
	
	int n, x;
	cin >> n >> x;
	
	int c[n];
	int a[x + 1];
	
	for(int i = 0; i < n; i++) cin >> c[i];
	
	a[0] = 1;
	
	for(int i = 1; i <= x; i++){
		a[i] = 0;
		for(int j = 0; j < n; j++){
			if(i >= c[j]) a[i] += a[i - c[j]];
			a[i] %= mod;
		}
	}
	
	cout << a[x] << endl;

	return 0;
}