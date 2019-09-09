#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, x;
	cin >> n >> x;
	
	int a[x + 1];
	memset(a, -1, sizeof(a));
	a[0] = 0;
	
	int h[n], s[n];
	for(int i = 0; i < n; i++) cin >> h[i];
	for(int i = 0; i < n; i++) cin >> s[i];
	
	int maxv = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = x; j >= h[i]; j--){
			if(a[j - h[i]] == -1) continue;
			
			a[j] = max(a[j], a[j - h[i]] + s[i]);
			maxv = max(maxv, a[j]);
		}
	}
	
	cout << maxv << endl;

	return 0;
}