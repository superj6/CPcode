#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

const int inf = 1000000007;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, x;
	cin >> n >> x;
	
	int c[n];
	int a[x + 1];
	
	for(int i = 0; i < n; i++) cin >> c[i];
	
	a[0] = 0;
	
	for(int i = 1; i <= x; i++){
		a[i] = inf;
		for(int j = 0; j < n; j++){
			if(i >= c[j]) a[i] = min(a[i], a[i - c[j]] + 1);
		}
	}
	
	cout << (a[x] == inf ? -1 : a[x]) << endl;

	return 0;
}