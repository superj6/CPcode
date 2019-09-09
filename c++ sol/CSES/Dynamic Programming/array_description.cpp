#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const long mod = 1000000007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	long a[n][m + 1];
	memset(a, 0, sizeof(a));
	
	for(int i = 0; i < n; i++){
		int c;
		cin >> c;
		
		if(c == 0){
			if(i == 0){
				for(int j = 1; j <= m; j++) a[i][j] = 1;
			}else{
				for(int j = 1; j <= m; j++){
					for(int k = j - 1; k <= min(j + 1, m); k++) a[i][j] += a[i - 1][k];
					a[i][j] %= mod;
				} 
			}
		}else{
			if(i == 0){
				a[i][c] = 1;
			}else{
				for(int k = c - 1; k <= min(c + 1, m); k++) a[i][c] += a[i - 1][k];
				a[i][c] %= mod;
			}
		}
	}
	
	long sum = 0;
	
	for(int i = 1; i <= m; i++) sum = (sum + a[n - 1][i]) % mod;
	
	cout << sum << endl;

	return 0;
}