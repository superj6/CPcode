#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

int n, m;
bool f;

void answer(){
	cin >> n >> m;
	
	if(n < m){
		swap(n, m);
		f = 1;
	}else f = 0;
	
	int ret = 0;
	int a[n][m];
	memset(a, 0, sizeof(a));
	for(int i = 0, c = n / 2; i < (m - 1) / 2; i++)
	for(int j = 0; j < n; j++, c--){
		a[j][ret] = 1;
		if(!c){
			ret++;
			c = n / 2 + 1;
		}
	}
	ret += n;
	
	if(f) swap(n, m);
	cout << ret << endl;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cout << ((f ? !a[j][i] : a[i][j]) ? '-' : '+');
		}
		cout << endl;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}