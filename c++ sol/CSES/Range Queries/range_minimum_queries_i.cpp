#include <iostream>
#include <cstdio>
#include <algorithm>
#include <math.h>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	int s[18][n];
	for(int i = 0; i < n; i++){
		cin >> s[0][i];
	}
	
	for(int i = 1; i < 18; i++){
		for(int j = 0; j + (1 << i) <= n; j++){
			s[i][j] = min(s[i - 1][j], s[i - 1][j + (1 << (i - 1))]);
		}
	}
	
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		
		int j = log2(b - a + 1);
		cout << min(s[j][a], s[j][b - (1 << j) + 1]) << endl;
	}

	return 0;
}