/*
This is code of SuperJ6 for Codeforces.
Don't copy my code during f*kin' contests.

2.71828182845904523536
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int m = 18;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, q;
	cin >> n >> q;
	
	int st[n][m];
	st[0][0] = -2;
	for(int i = 1; i < n; i++){
		cin >> st[i][0];
		st[i][0]--;
	} 
	
	for(int j = 1; j < m; j++){
		for(int i = 0; i < n; i++){
			st[i][j] = st[i][j - 1] == -2 ? -2 : st[st[i][j - 1]][j - 1];
		}
	}
	
	for(int i = 0; i < q; i++){
		int x, k;
		cin >> x >> k;
		x--;
		for(int j = 0; j < m && x != -2; j++) if(k & (1 << j)) x = st[x][j];
		cout << (x + 1) << endl;
	}

	return 0;
}